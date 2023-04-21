import uno
import os
import uuid
import subprocess
import sys
import time
from random import randint

#Terminal command:
#macOS: /Applications/LibreOffice.app/Contents/MacOS/soffice --headless --invisible --nocrashreport --nodefault --nofirststartwizard --nologo --norestore --accept='socket,host=localhost,port=2002,tcpNoDelay=1;urp;StarOffice.ComponentContext'
#Windows: "C:\Program Files\LibreOffice\program\soffice.exe" --calc --accept="socket,host=localhost,port=2002;urp;"

#Use python from:
#macOS: /Applications/LibreOffice.app/
#Windows: C:\Program Files\LibreOffice\program\python.exe

NoConnectException = uno.getClass(
        "com.sun.star.connection.NoConnectException")
def init_office():
    connection_string = "uno:socket,host=localhost,port=2002;urp;\
StarOffice.ComponentContext"
    oLocal = uno.getComponentContext()
    oResolver = \
        oLocal.ServiceManager.createInstanceWithContext(
                        "com.sun.star.bridge.UnoUrlResolver", oLocal)
    if oResolver:
        oContext = oResolver.resolve(connection_string)

def start_office(timeout=30, attempt_period=0.1, office="/Applications/LibreOffice.app/Contents/MacOS/soffice --headless --invisible --nocrashreport --nodefault --nofirststartwizard --nologo --norestore --accept='socket,host=localhost,port=2002,tcpNoDelay=1;urp;StarOffice.ComponentContext'"):
    def start_office_instance(office):
        if os.fork():
            return

        try:
            retcode = subprocess.call(office, shell=True)
            if retcode < 0:
                print (sys.stderr,
                       "Office was terminated by signal",
                       -retcode)
            elif retcode > 0:
                print (sys.stderr,
                       "Office returned",
                       retcode)
        except OSError as e:
            print (sys.stderr, "Execution failed:", e)
        raise SystemExit()

    waiting = False
    try:
        init_office()
    except NoConnectException as e:
        waiting = True
        start_office_instance(office)

    if waiting:
        steps = int(timeout/attempt_period)
        exception = None
        for i in range(steps + 1):
            try:
                init_office()
                break
            except NoConnectException as e:
                exception = e
                time.sleep(attempt_period)
        else:
            if exception:
                raise NoConnectException(exception)
            else:
                raise NoConnectException()


def generate(wishestable, n):
    result = []
    usedwishes = [[False]*len(wishestable[0]), [False]*len(wishestable[1]), [False]*len(wishestable[2])]
    ctr = [0, 0, 0]
    for i in range(n):
        tmp_whs = []
        for k in range(3):
            arnd = randint(0, len(wishestable[k]) - 1)
            while (usedwishes[k][arnd]):
                arnd += 1
                if (arnd == len(wishestable[k])):
                    arnd = 0
            usedwishes[k][arnd] = True
            ctr[k] += 1
            if (ctr[k] == len(wishestable[k])):
                usedwishes[0] = [False]*len(wishestable[k])
                ctr[k] = 0
            tmp_whs.append(wishestable[k][arnd])
        result.append(tmp_whs)
    return result

def check(wishes, names):
    if len(wishes[0])*len(wishes[1])*len(wishes[2]) >= len(names):
        return True
    else:
        return False

def connect():
    local_ctx = uno.getComponentContext()
    smgr_local = local_ctx.ServiceManager
    resolver = smgr_local.createInstanceWithContext("com.sun.star.bridge.UnoUrlResolver", local_ctx)
    url = "uno:socket,host=localhost,port=2002,tcpNoDelay=1;urp;StarOffice.ComponentContext"
    uno_ctx = resolver.resolve(url)
    uno_smgr = uno_ctx.ServiceManager
    desktop = uno_smgr.createInstanceWithContext("com.sun.star.frame.Desktop", uno_ctx)
    return desktop


def readCalcDoc(filepath):
    names = []
    wisheslist = []
    wishes = []
    path = os.path.abspath("./" + filepath)
    uno_url = uno.systemPathToFileUrl(path)
    document = desktop.loadComponentFromURL(uno_url, "_default", 0, ())
    sheets = document.getSheets()
    names_sheet = sheets.getByName("NAMES")
    wishes_sheet = sheets.getByName("WISHES")
    conf_sheet = sheets.getByName("CONF")
    i = 0
    while(names_sheet.getCellByPosition(0, i).String != ""):
        names.append(names_sheet.getCellByPosition(0, i).String)
        i += 1

    i, j = 0, 0
    while (wishes_sheet.getCellByPosition(i, j).String != ""):
        while (wishes_sheet.getCellByPosition(i, j).String != ""):
            wishes.append(wishes_sheet.getCellByPosition(i, j).String)
            j += 1
        wisheslist.append(wishes)
        wishes = []
        j = 0
        i += 1
    path = conf_sheet.getCellByPosition(1, 0).String
    filters = ()
    document.storeToURL(uno_url, filters)
    return names, wisheslist, path


def CreateWriterFile(template, names, wishes):
    PropertyValue = uno.getClass('com.sun.star.beans.PropertyValue')
    inProps = PropertyValue("Hidden", 0, True, 0),  # this is a tuple
    path_template = os.path.abspath(template)
    uno_url_template = uno.systemPathToFileUrl(path_template)
    resultfile = desktop.loadComponentFromURL("private:factory/swriter", "_blank", 0, inProps)
    templatefile = desktop.loadComponentFromURL(uno_url_template, "_default", 0, inProps)
    frame_tmp = templatefile.getCurrentController().Frame
    frame_result = resultfile.getCurrentController().Frame
    ctx = uno.getComponentContext()
    sm = ctx.ServiceManager
    dispatcher = sm.createInstanceWithContext("com.sun.star.frame.DispatchHelper", ctx)

    for i in range(len(names)):
        dispatcher.executeDispatch(frame_tmp, ".uno:SelectAll", "", 0, ())
        dispatcher.executeDispatch(frame_tmp, ".uno:Copy", "", 0, ())
        dispatcher.executeDispatch(frame_result, ".uno:Paste", "", 0, ())
        marks = resultfile.getBookmarks()
        namemark = marks.getByName("NAME" + ((" Copy " + str(i)) if i != 0 else ""))
        namemark.getAnchor().setString(names[i])
        w1mark = marks.getByName("WISH1" + ((" Copy " + str(i)) if i != 0 else ""))
        w1mark.getAnchor().setString(wishes[i][0])
        w2mark = marks.getByName("WISH2" + ((" Copy " + str(i)) if i != 0 else ""))
        w2mark.getAnchor().setString(wishes[i][1])
        w3mark = marks.getByName("WISH3" + ((" Copy " + str(i)) if i != 0 else ""))
        w3mark.getAnchor().setString(wishes[i][2])

    result_path = os.path.abspath('./resultfile (' + str(uuid.uuid4()) + ').odt')
    uno_url_result = uno.systemPathToFileUrl(result_path)
    filters = ()
    resultfile.storeToURL(uno_url_result, filters)


start_office()
desktop = connect()
print("Читаю файлы...")
names, wishes, templatepath = readCalcDoc("test.ods")
print("Достаю калькулятор...")
if (check(wishes, names)):
    #print(names, wishes)
    print("Сочиняю поздравления...")
    listwishes = generate(wishes, len(names))
    #print(listwishes)
    print("Записываю...")
    CreateWriterFile(templatepath, names, listwishes)
    print("Готово!")
else:
    print("ALARM! Мало поздравлений!!!")
desktop.terminate()