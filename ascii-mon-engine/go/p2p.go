// p2p.go
package main

import "C"
import (
	"fmt"
	"net"
	"sync"
	"time"

	"github.com/pion/stun"
)

var (
	conn        *net.UDPConn
	messageLock sync.Mutex
	lastMessage string
	publicAddr  string
	peerAddr    *net.UDPAddr
)

//export Host
func Host() {
	// 1. Bind to a random UDP port on all interfaces
	laddr, err := net.ResolveUDPAddr("udp", ":0")
	if err != nil {
		publicAddr = "Error: Failed to resolve local UDP address"
		return
	}

	conn, err = net.ListenUDP("udp", laddr)
	if err != nil {
		publicAddr = "Error: Failed to open UDP socket"
		return
	}

	// 2. Start listening thread
	go listen()

	// 3. Discover public IP:port via STUN
	stunConn, err := stun.Dial("udp", "stun.l.google.com:19302")
	if err != nil {
		publicAddr = "Error: STUN dial failed"
		return
	}
	defer stunConn.Close()

	var mappedAddr stun.XORMappedAddress
	err = stunConn.Do(
		stun.MustBuild(stun.TransactionID, stun.BindingRequest),
		func(res stun.Event) {
			if res.Error != nil {
				err = res.Error
				return
			}
			err = mappedAddr.GetFrom(res.Message)
		},
	)

	if err != nil {
		publicAddr = "Error: STUN request failed"
		return
	}

	// 4. Save public address string for GetPublicIP()
	publicAddr = fmt.Sprintf("%s:%d", mappedAddr.IP.String(), mappedAddr.Port)
}

//export Connect
func Connect(ip *C.char) {
	remote := C.GoString(ip)
	remoteAddr, err := net.ResolveUDPAddr("udp", remote)
	if err != nil {
		fmt.Println("[ERROR] ResolveUDPAddr failed:", err)
		return
	}

	laddr, _ := net.ResolveUDPAddr("udp", ":0")
	conn, err = net.ListenUDP("udp", laddr)
	if err != nil {
		fmt.Println("[ERROR] ListenUDP failed:", err)
		return
	}

	peerAddr = remoteAddr
	go listen()

	fmt.Println("[CONNECTING TO]", remoteAddr.String())
	for i := 0; i < 5; i++ {
		_, err := conn.WriteToUDP([]byte("punch"), remoteAddr)
		fmt.Println("[PUNCH]", i+1, "->", remoteAddr.String(), err)
		time.Sleep(300 * time.Millisecond)
	}
}

//export Send
func Send(data *C.char) {
	msg := C.GoString(data)
	if peerAddr != nil {
		_, err := conn.WriteToUDP([]byte(msg), peerAddr)
		fmt.Println("[SEND] To", peerAddr.String(), "->", msg, err)
	} else {
		fmt.Println("[SEND] peerAddr is nil, can't send")
	}
}

//export HasMessage
func HasMessage() C.int {
	messageLock.Lock()
	defer messageLock.Unlock()
	if lastMessage != "" {
		return 1
	}
	return 0
}

//export GetLastMessage
func GetLastMessage() *C.char {
	messageLock.Lock()
	defer messageLock.Unlock()
	msg := lastMessage
	lastMessage = ""
	return C.CString(msg)
}

func listen() {
	buf := make([]byte, 1024)
	for {
		n, addr, err := conn.ReadFromUDP(buf)
		if err != nil {
			fmt.Println("Read error:", err)
			continue
		}
		fmt.Printf("[RECEIVED] %d bytes from %s: %s\n", n, addr.String(), string(buf[:n]))

		messageLock.Lock()
		lastMessage = string(buf[:n])
		messageLock.Unlock()

		// Save peer address if it's not already saved
		if peerAddr == nil {
			peerAddr = addr
			fmt.Println("[PEER SET] Using", addr.String(), "as peer")
		}
	}
}

//export GetPublicIP
func GetPublicIP() *C.char {
	return C.CString(publicAddr)
}

func discoverMappedAddress() *net.UDPAddr {
	stunServer := "stun.l.google.com:19302"
	conn, err := stun.Dial("udp", stunServer)
	if err != nil {
		return nil
	}
	defer conn.Close()

	var mappedAddr stun.XORMappedAddress

	err = conn.Do(
		stun.MustBuild(stun.TransactionID, stun.BindingRequest),
		func(res stun.Event) {
			if res.Error != nil {
				err = res.Error
				return
			}
			err = mappedAddr.GetFrom(res.Message)
		},
	)

	if err != nil {
		return nil
	}

	return &net.UDPAddr{
		IP:   mappedAddr.IP,
		Port: mappedAddr.Port,
	}
}

func main() {}
