
function addCSSRule(selector, newRule) {
    var mySheet = document.styleSheets[0];
    if (mySheet.addRule) {
        mySheet.addRule(selector, newRule);								// For Internet Explorer
    } else {
        ruleIndex = mySheet.cssRules.length;
        mySheet.insertRule(selector + '{' + newRule + ';}', ruleIndex);   // For Firefox, Chrome, etc.
    }
}


function layoutPage()
{
    var content = document.getElementById("content");
    var chapters = content.children;
    var contentHeight = content.offsetHeight;

    for (var i = 0; i < chapters.length; i++)
    {
        var chapter = chapters[i];
        var offsetHeight = chapter.offsetHeight;
        var height = contentHeight;
        while(height<offsetHeight)
        {
            height+=contentHeight;
        }

        chapter.setAttribute("style","height:"+height+"px;");
    }
}

function layoutChapter(cid)
{
    var content = document.getElementById("content");
    var chapter = document.getElementById(cid);
    var contentHeight = content.offsetHeight;
    var offsetHeight = chapter.offsetHeight;
    var height = contentHeight;
    while(height < offsetHeight)
    {
        height+=contentHeight;
    }
    chapter.setAttribute("style","height:"+height+"px;");
}

function setFontSize(sizeFont)
{
    var content = document.getElementById("content");
    var chapters = content.children;
    for (var i = 0; i < chapters.length; i++)
    {
            var chapter = chapters[i];
            chapter.removeAttribute("style");
    }
//    addCSSRule('body', '-webkit-text-size-adjust: '+sizeFont+'%%;');
    addCSSRule("#content", "font-size: "+sizeFont+"%%;");
    layoutPage();
}

function appendChapter(cID, cText)
{
    var model = document.getElementById("chpaterModel");
    var chapter = model.cloneNode(true);
    chapter.setAttribute("id", cID);
    chapter.innerHTML = cText;
    var content = document.getElementById("content");
    content.appendChild(chapter);
    layoutChapter(cID);
}

function deleteChapter(cID)
{
    var content = document.getElementById("content");
    var chapter = document.getElementById(cID);
    content.removeChild(chapter);
}

function removeChapter()
{
    var content = document.getElementById("content");
    content.removeChild(content.children[0]);
}

function identifierFromPoint(x,y)
{
    var element = document.elementFromPoint(x, y);
    if (element.tagName == "P" || element.tagName == "p" ||
        element.tagName == "H3" || element.tagName == "h3") {
        return element.parentElement.id;
    }
    else {
        return element.id;
    }
}

function lockHeight(height)
{
    document.body.setAttribute("style", "height: "+(height-30) + "px;");
    document.documentElement.style.webkitUserSelect='none';
    document.documentElement.style.webkitTouchCallout='none';
}

function setTextColorLight(light)
{
    var content = document.getElementById("content");
    if (light == 1) {
        content.setAttribute("style","color : #909090;");
    }
    else {
        content.setAttribute("style","color : #101010;");
    }
}

