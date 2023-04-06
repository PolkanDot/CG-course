var canv = document.getElementById('canvas');
var ctx = canv.getContext('2d');
imageHeight = 0;
imageWidth = 0;

function DownloadCanvasAsImage() {
    let downloadLink = document.createElement('a');
    downloadLink.setAttribute('download', 'CanvasAsImage.jpeg');
    canv.toBlob(function (blob) {
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
        image.onload = function () {
            image.id = "downloadImage"
            imageHeight = this.height;
            imageWidth = this.width;
            DisplayCanvas();
            var positionInfoCanv = canv.getBoundingClientRect();
            ctx.drawImage(image, 0, 0, imageWidth, imageHeight, 0, 0, positionInfoCanv.width, positionInfoCanv.height);
        }
        document.body.appendChild(image);
    }
    reader.readAsDataURL(file); 
}

function DrowImage() {
    DisplayCanvas();
    var img = document.getElementById("downloadImage");
    var positionInfoCanv = canv.getBoundingClientRect();
    ctx.drawImage(img, 0, 0, imageWidth, imageHeight, 0, 0, positionInfoCanv.width, positionInfoCanv.height);
}
