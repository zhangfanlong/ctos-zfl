function obj2str(o) {  
    var r = [];  
    if (typeof o == "string") return "\"" + o.replace(/([\'\"\\])/g, "\\$1").replace(/(\n)/g, "\\n").replace(/(\r)/g, "\\r").replace(/(\t)/g, "\\t") + "\"";  
    if (typeof o == "object") {  
        if (!o.sort) {  
            for (var i in o)  
                r.push("\"" + i + "\":" + obj2str(o[i]));  
            if (!!document.all && !/^\n?function\s*toString\(\)\s*\{\n?\s*\[native code\]\n?\s*\}\n?\s*$/.test(o.toString)) {  
                r.push("toString:" + o.toString.toString());  
            }  
            r = "{" + r.join() + "}" 
        } else {  
            for (var i = 0; i < o.length; i++)  
                r.push(obj2str(o[i]))  
            r = "[" + r.join() + "]" 
        }  
        return r;  
    }  
    return o.toString();  
} 

function createClickListener(targetAnchor)
{
  return function(ev){
    if (targetAnchor.target == "_top" || targetAnchor.target == "_blank" 
      || targetAnchor.target == "_self" || targetAnchor.target == "_parent" 
      || targetAnchor.target.length == 0)
    {
      chrome.extension.sendRequest({msgType: 'jump', pageId: window.name, pageJumpType: 'anchorJump', pageJumpURL: targetAnchor.href, pageJumpTarget: targetAnchor.target}, function(response) {
        console.log(response.farewell);});
      ev.preventDefault();
    }
    else
    {
	alert(targetAnchor.target);
    }
  };
}

function checkGetCookies()
{
	var getCookiesInput = document.getElementById("getCookiesInput");
	chrome.extension.sendRequest({msgType: 'getCookies'}, function(response)
	{
		getCookiesInput.value = response.cookies;
	});
//	getCookiesInput.value = "xxxxx";
//		window.clearInterval();
}

function checkSetCookies()
{
	var setCookiesInput = document.getElementById("setCookiesInput");
	if (setCookiesInput.value != "")
	{
		console.log("sv:" + setCookiesInput.value);
		chrome.extension.sendRequest({msgType: 'setCookies', cookies: setCookiesInput.value}, function(response){});
		setCookiesInput.value = "";
	}
	else
	{
		console.log("nothing");
	}
}

function checkDelCookies()
{
	var delCookiesInput = document.getElementById("delCookiesInput");
	if (delCookiesInput.value == "1")
	{
		chrome.extension.sendRequest({msgType: 'delCookies'}, function(response){});
		delCookiesInput.value = "0";
	}
}

if(top!=this && parent == top){
  chrome.extension.sendRequest({msgType: 'jump', pageId: window.name, pageJumpType: 'selfJump', pageJumpURL: document.URL, pageJumpTitle: document.title, pageJumpTarget: ""}, function(response) {
        console.log(response.farewell);});

　// 在frame中时处理
  var nodes = [];
  var result = document.evaluate(
    '//a[@href]',
    document, null, XPathResult.UNORDERED_NODE_ITERATOR_TYPE, null);
  while (item = result.iterateNext()) {
    nodes.push(item);
  }
  for (var i = 0; i < nodes.length; i++) {
    //nodes[i].setAttribute('href', 'http://liujuncheng.org');
    nodes[i].addEventListener('click', createClickListener(nodes[i]), false);
  }
}
else
{
  var setCookiesInput = document.createElement("input");
  setCookiesInput.setAttribute("id", "setCookiesInput");
  setCookiesInput.setAttribute("type", "hidden");
  setCookiesInput.setAttribute("value", "");
  document.body.appendChild(setCookiesInput);

  var getCookiesInput = document.createElement("input");
  getCookiesInput.setAttribute("id", "getCookiesInput");
  getCookiesInput.setAttribute("type", "hidden");
  document.body.appendChild(getCookiesInput);

  var delCookiesInput = document.createElement("input");
  delCookiesInput.setAttribute("id", "delCookiesInput");
  delCookiesInput.setAttribute("type", "hidden");
  delCookiesInput.setAttribute("value", "0");
  document.body.appendChild(delCookiesInput);


  setInterval("checkGetCookies()", 1000);
  setInterval("checkSetCookies()", 1000);
  setInterval("checkDelCookies()", 1000);

  chrome.extension.onRequest.addListener(
  function(request, sender, sendResponse) {
    console.log(sender.tab ?
                "from a content script:" + sender.tab.url :
                "from the extension");
console.log(obj2str(request));
    if (request.pageJumpType == 'anchorJump' || request.pageJumpType == 'selfJump')
    {
      var pageJumpForm = document.createElement("form");
      pageJumpForm.setAttribute("name", "pageJumpForm");
      pageJumpForm.setAttribute("id", request.pageId);
      
      var pageJumpType = document.createElement("input");
      pageJumpType.setAttribute("type", "hidden");
      pageJumpType.setAttribute("id", "pageJumpType");
      pageJumpType.setAttribute("value", obj2str(request));
      pageJumpForm.appendChild(pageJumpType);

      /*var pageJumpType = document.createElement("input");
      pageJumpType.setAttribute("type", "hidden");
      pageJumpType.setAttribute("id", "pageJumpType");
      pageJumpType.setAttribute("value", request.pageJumpType);
      pageJumpForm.appendChild(pageJumpType);

      var pageJumpURL = document.createElement("input");
      pageJumpURL.setAttribute("type", "hidden");
      pageJumpURL.setAttribute("id", "pageJumpURL");
      pageJumpURL.setAttribute("value", request.pageJumpURL);
      pageJumpForm.appendChild(pageJumpURL);

      var pageJumpTarget = document.createElement("input");
      pageJumpTarget.setAttribute("type", "hidden");
      pageJumpTarget.setAttribute("id", "pageJumpTarget");
      pageJumpTarget.setAttribute("value", request.pageJumpTarget);
      pageJumpForm.appendChild(pageJumpTarget);

      var pageJumpTitle = document.createElement("input");
      pageJumpTitle.setAttribute("type", "hidden");
      pageJumpTitle.setAttribute("id", "pageJumpTitle");
      pageJumpTitle.setAttribute("value", request.pageJumpTitle);
      pageJumpForm.appendChild(pageJumpTitle);
*/
      document.body.appendChild(pageJumpForm);


      //document.getElementById('pageJumpType').value = request.pageJumpType;
      //document.getElementById('pageJumpURL').value = request.pageJumpURL;
      //document.getElementById('pageJumpTarget').value = request.pageJumpTarget;
      sendResponse({farewell: "goodbye"});
    }
    else
      sendResponse({}); // snub them.
  });
}
