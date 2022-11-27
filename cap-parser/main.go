package main

import (
    "encoding/xml"
    "fmt"
    "io/ioutil"
    "os"
)

func main() {
    var alertObject Alert
    parser("example1.xml", &alertObject)
    fmt.Println(alertObject)
    
    /* FIXME 
    Output XML file, incorrect in alert tag, needs to
    clean tags with empty inner value

    deparser(alertObject, "test.xml")
    
    */
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
    // validation
    byteValue, _ := xml.Marshal(alert)
    os.WriteFile(outFilePath, byteValue, 0664)
}
