package main

import (
	"encoding/xml"
)

type Alert struct {
	XMLName     xml.Name  	`xml:"alert"`
	Xmlns       *string   	`xml:"xmlns,attr"`
	Identifier  *string   	`xml:"identifier"`
	Sender      *string   	`xml:"sender"`
	Sent        *string   	`xml:"sent"`
	Status      *string   	`xml:"status"`
	MsgType     *string   	`xml:"msgType"`
	Source      *string   	`xml:"source"`
	Scope       *string   	`xml:"scope"`
	Restriction *string   	`xml:"restriction"`
	Addresses   *Addresses	`xml:"addresses"`
	Codes       *[]string 	`xml:"code"`
	Note        *Note     	`xml:"note"`
	References  *string   	`xml:"references"`
	Incidents   *string   	`xml:"incidents"`
	Infos       *[]Info   	`xml:"info"`
}

type Addresses struct{
	Content		string		`xml:",innerxml"`
}

type Note struct{
	Content		string		`xml:",innerxml"`
}

type Info struct {
	XMLName       xml.Name     `xml:"info"`
	Language      *string      `xml:"language"`
	Category      *[]string    `xml:"category"`
	Event         *string      `xml:"event"`
	ResponsesType *[]string    `xml:"responseType"`
	Urgency       *string      `xml:"urgency"`
	Severity      *string      `xml:"severity"`
	Certainty     *string      `xml:"certainty"`
	Audience      *string      `xml:"audience"`
	EventCode     *[]EventCode `xml:"eventCode"`
	Effective     *string      `xml:"effective"`
	Onset         *string      `xml:"onset"`
	Expires       *string      `xml:"expires"`
	SenderName    *string      `xml:"senderName"`
	Headline      *string      `xml:"headline"`
	Description   *string      `xml:"description"`
	Instruction   *string      `xml:"instruction"`
	Web           *string      `xml:"web"`
	Contact       *string      `xml:"contact"`
	Parameters    *[]Parameter `xml:"parameter"`
	Resources     *[]Resource  `xml:"resource"`
	Areas         *[]Area      `xml:"area"`
}

type Parameter struct {
	XMLName   xml.Name `xml:"parameter"`
	ValueName *string  `xml:"valueName"`
	Value     *string  `xml:"value"`
}

type EventCode struct {
	XMLName   xml.Name `xml:"eventCode"`
	ValueName *string  `xml:"valueName"`
	Value     *string  `xml:"value"`
}

type Resource struct {
	XMLName      xml.Name `xml:"resource"`
	ResourceDesc *string  `xml:"resourceDesc"`
	MimeType     *string  `xml:"mimeType"`
	Size         *string  `xml:"size"`
	Uri          *string  `xml:"uri"`
	DerefUri     *string  `xml:"derefUri"`
	Digest       *string  `xml:"digest"`
}

type Area struct {
	XMLName   xml.Name   `xml:"area"`
	AreasDesc *string    `xml:"areaDesc"`
	Polygons  *[]string  `xml:"polygon"`
	Circles   *[]string  `xml:"circle"`
	Geocodes  *[]Geocode `xml:"geocode"`
	Altitude  *string    `xml:"altitude"`
	Ceiling   *string    `xml:"ceiling"`
}

type Geocode struct {
	XMLName   xml.Name `xml:"geocode"`
	ValueName *string  `xml:"valueName"`
	Value     *string  `xml:"value"`
}
