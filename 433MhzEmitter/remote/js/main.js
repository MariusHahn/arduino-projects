window.onload = () => {
    'use strict';
    if ('serviceWorker' in navigator) {
        navigator.serviceWorker
            .register('./js/sw.js');
    }
}

function getResponseIframe() {
    return document.getElementById("response")
}

getResponseIframe().onload = colorText;

function getEmittedCode() {
    return getResponseIframe()
    .contentWindow
    .document
    .body
    .innerHTML
    .split(":")[1].trim()
}

function getElementIdAndColor(code) {
    const green = "#00ff00"
    const red = "#ff0000"
    switch(code) {
        case "2221916":
            return {ids: ["a", "c", "d"], color: green}
        case "2416012":
            return {ids: ["a", "c", "d"], color: red}
        case "2126053":
            return {ids: ["b"], color: green}
        case "2263253":
            return {ids: ["b"], color: red}
        case "2416014":
            return {ids: ["c"], color: green}
        case "2309998":
            return {ids: ["c", "a"], color: red}
        case "2263255":
            return {ids: ["d"], color: green}
        case "2126055":
            return {ids: ["d", "a"], color: red}
    }
}

function colorText() {
    const emittedCode = getEmittedCode()
    const colorAndCode = getElementIdAndColor(emittedCode);
    console.log(colorAndCode)
    colorAndCode.ids
        .map(id => document.getElementById(id))
        .forEach(el => el.style.color = colorAndCode.color);
}