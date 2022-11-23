package main

import (
    "encoding/xml"
    "fmt"
    "io/ioutil"
    "os"
)

func main() {
    xmlFile, err := os.Open("example1.xml")
    if err != nil {
        fmt.Println(err)
    }
    defer xmlFile.Close()

    byteValue, _ := ioutil.ReadAll(xmlFile)

    var alert Alert
    xml.Unmarshal(byteValue, &alert)

    fmt.Println(alert)
}