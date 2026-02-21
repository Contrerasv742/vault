package main

import (
    "encoding/json"
    "fmt"
    "log"
    "os"
)

/* TODO: Look into nvim.undo-tree */
func main() {
    filePath := "data.json"

    content, err := os.ReadFile(filePath)

    if err != nil {
        log.Fatal(err)
    }

    var data map[string]interface{}
    err = json.Unmarshal(content, &data)

    if err != nil {
        log.Fatal(err)
    }

    passwords := data["passwords"].([]interface{})
    for _, password := range passwords {
        pass := password.(map[string]interface{})
        fmt.Println("name:", pass["name"])
        fmt.Println("\tusername:", pass["username"])
        fmt.Println("\turl", pass["url"])
        fmt.Println("\tpassword:", pass["password"])
    }
}
