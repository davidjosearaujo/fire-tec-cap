package main

import (
	//"bytes"
	"encoding/xml"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
        var alertObject Alert
        infile := os.Args[1]
        outfile := os.Args[2]
        parser(infile, &alertObject)
        deparser(alertObject, outfile)
}

func parser(filePath string, alertObject *Alert) {
    xmlFile, err := os.Open(filePath)
    if err != nil {
        fmt.Println(err)
    }
    // validation
    defer xmlFile.Close()
    byteValue, _ := ioutil.ReadAll(xmlFile)
    xml.Unmarshal(byteValue, &alertObject)
}

func deparser(alert Alert, outFilePath string) {
    byteValue, _ := xml.Marshal(alert)
    ioutil.WriteFile(outFilePath, byteValue, 0664)
}
