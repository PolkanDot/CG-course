var canv = document.getElementById('canvas');
var ctx = canv.getContext('2d');
var isMouseDown = false;
var lineWidth = 10;
// глобальные переменные!
canv.width = window.innerWidth * 0.95;
canv.height = window.innerHeight * 0.75;
var offsetY = 155;
var offsetX = 38;
ctx.lineWidth = lineWidth;

canv.addEventListener('mousedown', function () {
    isMouseDown = true;
});
canv.addEventListener('mouseup', function () {
    isMouseDown = false;
    ctx.beginPath();
});
canv.addEventListener('mousemove', function (e) {
    if (isMouseDown) {
        ctx.lineTo(e.clientX - offsetX, e.clientY - offsetY);
        ctx.stroke();

        ctx.beginPath();
        ctx.arc(e.clientX - offsetX, e.clientY - offsetY, lineWidth / 2, 0, Math.PI * 2);
        ctx.fill();

        ctx.beginPath();
        ctx.moveTo(e.clientX - offsetX, e.clientY - offsetY);
    }
});
// после смены цвета первая точка предыдущего цвета
function ChangeDrawingColor(color) {
    ctx.strokeStyle = color;
    ctx.fillStyle = color;
}
// нужно, чтбобы без картинки фон был полупразрвчным
function FillCanvas() {
    color = ctx.fillStyle;
    ctx.fillStyle = "#FFFFFF";
    ctx.fillRect(0, 0, canv.width, canv.height);
    ctx.fillStyle = color;
}

function DisplayCanvas() {
    canv.style.display = 'block';
}

function UpdateCanvas() {
    DisplayCanvas();
    FillCanvas();
}