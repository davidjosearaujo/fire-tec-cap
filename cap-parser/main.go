package main

import (
	"os"
    "fmt"
    "github.com/DavidAraujo98/cap-parser"
)

// TESTING
func main() {
    var alertObject cap.Alert
    var byteValue = cap.ReadFileToCAP(os.Args[1])
    cap.Parser(byteValue, &alertObject)
    fmt.Println(string(byteValue))
    byteValue = cap.Deparser(alertObject)
    cap.WriteCAPToFile(byteValue, os.Args[2])
}
// =======