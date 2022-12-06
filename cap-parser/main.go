package main

import (
	"os"
    "github.com/DavidAraujo98/cap-parser"
)

func main() {
    var alertObject cap.Alert
    cap.Parser(os.Args[1], &alertObject)
    cap.Deparser(alertObject, os.Args[2])
}