package main

import (
	"encoding/xml"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
    var alertObject Alert
    Parser(os.Args[1], &alertObject)
    Deparser(alertObject, os.Args[2])
}

func Parser(inFilePath string, alertObject *Alert) {
    xmlFile, err := os.Open(inFilePath)
    if err != nil {
        fmt.Println(err)
    }
    defer xmlFile.Close()
    byteValue, _ := ioutil.ReadAll(xmlFile)
    xml.Unmarshal(byteValue, &alertObject)
}

func Deparser(alert Alert, outFilePath string) {
    byteValue, _ := xml.Marshal(alert)
    ioutil.WriteFile(outFilePath, byteValue, 0664)
}
