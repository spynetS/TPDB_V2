#!/usr/bin/env python3
import json


path = "./json.json"

def getList(prompt):
    print(prompt, "(end with done)")
    li = []
    value = ""
    while value != "done":
        value = input("> ")
        li.append(value)
    return li

def isMainCodeInErrors(errors, mainCode):
    index = 0
    for error in errors:
        print(error["title"])
        if error["title"] == mainCode: return index
        index += 1
    return -1

def create(args):
    print("Create new error code")
    mainCode = input("What main title? ")
    title = input("What sub title? ")
    desc=input("What description? ")

    args = getList("What args? ")
    notes = getList("What notes? ")

    footer=input("What footer? ")

    print("Check its right:")
    print(mainCode)
    print(title)
    print(desc)
    print(args)
    print(notes)
    print(footer)

    if input("right? y/n ") == "y":
        with open(path,"r") as f:
            data = json.loads(f.read())
            sub = {
                "title":title,
                "Desc":desc,
                "Args":args,
                "Notes":notes,
                "Footer":footer
            }

            error = isMainCodeInErrors(data["errors"],mainCode)
            print(error)
            if error >= 0:
                data["errors"][error]["sub"].append(sub)
            else:
                data["errors"].append({
                    "title":mainCode,
                    "sub":[
                        sub
                    ]
                })

                with open(path,"w") as f:
                    json.dump(data,f,indent=4)
