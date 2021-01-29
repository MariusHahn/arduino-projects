window.onload = () => {
    'use strict';
    if ('serviceWorker' in navigator) {
        navigator.serviceWorker
            .register('./js/sw.js');
    }
}

const responseDiv = document.getElementById("response_div");
const responseIframe = document.getElementById("response");
responseIframe.onload = function() {
    const responseText = responseIframe.contentWindow.document.body.innerHTML;
    const displayContent = responseText.split(":")[1].trim()
    console.log(`response: ${displayContent}`)
    responseDiv.innerText = displayContent;
}
