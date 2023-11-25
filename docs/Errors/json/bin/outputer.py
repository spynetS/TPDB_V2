#!/usr/bin/env python3

import json

mainComp = '''
<div class="flex flex-row w-full flex flex-col">
  <h3 id="ID" class="text-2xl mb-4">TITLE1</h3>
  COMPS
</div>'''

subComp = '''
    <div class="pl-8 mb-12">
      <p id="ID" class="text-lg font-bold">TITLE2</p>
      <p class="text-lg ml-10">
        DESCRIPTION
      </p>
      <p class="text-lg ml-10">
        <b>Args:</b><br/>
        <div style="margin-left: 60px;" >
            ARGS
        </div>
      </p>

      <b>Notes:</b><br/>
        NOTES
        FOOTER
    </p>
  </div>
'''

argComp = '''
      <b>-</b>ARG<br/>
'''

noteComp = '''<span style="margin-left: 30px;"></span><b>-</b> NOTE <br/><br/>'''

def getNotes(notes):
    notecomps = ""
    for note in notes:
        notecomps+=f"{noteComp.replace('NOTE',note)}\n"
    return notecomps

def getArgs(args):
    argcomps = ""
    for arg in args:
        argcomps+=f"{argComp.replace('ARG',arg)}"
    return argcomps

def getSubs(subs):
    subcomps = ""
    for sub in subs:
        subcomp = subComp.replace("TITLE2",sub["title"])
        subcomp = subcomp.replace("ID",sub["title"].split(" ")[0][1:])
        subcomp = subcomp.replace("DESCRIPTION",sub["Desc"].replace("\n","<br>"))
        subcomp = subcomp.replace("ARGS",getArgs(sub["Args"]))
        subcomp = subcomp.replace("NOTES",getNotes(sub["Notes"]))
        subcomp = subcomp.replace("FOOTER",sub["Footer"].replace("\n","<br>"))
        subcomps += (subcomp)
    return subcomps

def getMainComp(main):
    comp = mainComp.replace("TITLE1",main["title"])
    comp = comp.replace("ID",main["title"].split(" ")[0][1:])
    comp = comp.replace("COMPS",getSubs(main["sub"]))

    return comp

def output(args):
    path = "./json.json"
    with open(path,"r") as f:
        data = json.loads(f.read())

    mains = ""
    for main in data["errors"]:
        mains+=(getMainComp(main))

    text = ""
    with open("template.html","r") as f:
        text = f.read()
        text = text.replace("__ERRORS__",mains)
    with open("index.html","w") as f:
        f.write(text)
