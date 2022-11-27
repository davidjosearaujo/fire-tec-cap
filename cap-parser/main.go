package main

import (
	"bytes"
	"encoding/json"
	"encoding/xml"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
    if len(os.Args) == 4 {
        var alertObject Alert
        infile := os.Args[2]
        outfile := os.Args[3]
        switch os.Args[1]{
            case "--parse":
                parser(infile, &alertObject)
                file, _ := json.MarshalIndent(alertObject, "", "\t")
                _ = ioutil.WriteFile(outfile, file, 0644)
            case "--deparse":
                deparser(alertObject, outfile)
        }
    }else{
        fmt.Println("You nedd to call with arguments\n")
        fmt.Println("Usage:\n\n\tmain <command> <input file> <output file>\n\nThe commands are:\n")
        fmt.Println("\t--parse\t\tConverts XML file into JSON file")
        fmt.Println("\t--deparse\tConverts JSON file into XML file\n")
        os.Exit(1)
    }   
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
    byteValue = bytes.Replace(byteValue, []byte("&#34;"), []byte("\""), -1) // Escaping the " was needed
    ioutil.WriteFile(outFilePath, byteValue, 0664)
}
