var canv = document.getElementById('canvas');
var ctx = canv.getContext('2d');
var isMouseDown = false;
var lineWidth = 10;

canv.width = window.innerWidth * 0.95;
canv.height = window.innerHeight * 0.75;
offsetY = 147;
offsetX = 38;

ctx.lineWidth = 10;

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
        ctx.arc(e.clientX - offsetX, e.clientY - offsetY, lineWidth/2, 0, Math.PI * 2);
        ctx.fill();

        ctx.beginPath();
        ctx.moveTo(e.clientX - offsetX, e.clientY - offsetY);
    }
});

function DownloadCanvasAsImage() {
    let downloadLink = document.createElement('a');
    downloadLink.setAttribute('download', 'CanvasAsImage.jpeg');
    let canvas = document.getElementById('canvas');
    canvas.toBlob(function (blob) {
        let url = URL.createObjectURL(blob);
        downloadLink.setAttribute('href', url);
        downloadLink.click();
    });
}

function CreateImage() {

    var el = document.getElementById("downloadImage");
    if (el != null)
    {
        el.remove();
    }

    var file = document.getElementById('files').files[0];
    var reader = new FileReader();
    reader.onload = function (e) {
        var image = document.createElement("img");
        image.src = e.target.result;
        image.id = "downloadImage"
        image.style.maxHeight = canv.style.height;
        image.style.maxWidth = canv.style.width;
        document.body.appendChild(image);
    }
    reader.readAsDataURL(file); 
}

function DrowImage() {
    var img = document.getElementById("downloadImage");
    ctx.drawImage(img, 0, 0)
}

function ChangeDrawingColor(color) {
    ctx.strokeStyle = color;
    ctx.fillStyle = color;
}

document.addEventListener("click", function (e) {
    let m = document.getElementById('menu');
    if (e.target.id != 'test' && e.target.id != 'menu') {
        m.style.opacity = 0;
    } else if (e.target.id == 'test') {
        m.style.opacity = (m.style.opacity != 1) ? 1 : 0;
    }
});