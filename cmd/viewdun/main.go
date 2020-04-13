package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"io/ioutil"
	"log"

	"github.com/pkg/errors"
)

func main() {
	flag.Parse()
	for _, tileIDBinPath := range flag.Args() {
		tileIDMap, err := genDun(tileIDBinPath)
		if err != nil {
			log.Fatalf("%+v", err)
		}
		dunPath := tileIDBinPath + ".dun"
		if err := dumpDun(dunPath, tileIDMap); err != nil {
			log.Fatalf("%+v", err)
		}
	}
}

func genDun(tileIDBinPath string) (*[40][40]uint8, error) {
	buf, err := ioutil.ReadFile(tileIDBinPath)
	if err != nil {
		return nil, errors.WithStack(err)
	}
	r := bytes.NewReader(buf)
	tileIDMap := new([40][40]byte)
	if err := binary.Read(r, binary.LittleEndian, tileIDMap); err != nil {
		return nil, errors.WithStack(err)
	}
	return tileIDMap, nil
}

func dumpDun(dunPath string, tileIDMap *[40][40]uint8) error {
	const (
		width  = 40
		height = 40
	)
	buf := make([]uint16, 0)
	buf = append(buf, width)
	buf = append(buf, height)
	for y := 0; y < 40; y++ {
		for x := 0; x < 40; x++ {
			buf = append(buf, uint16(tileIDMap[x][y]))
		}
	}
	b := &bytes.Buffer{}
	binary.Write(b, binary.LittleEndian, buf)
	if err := ioutil.WriteFile(dunPath, b.Bytes(), 0644); err != nil {
		return errors.WithStack(err)
	}
	return nil
}
