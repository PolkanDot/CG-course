window.onload = () => {
  const canvas = document.getElementById('letters');
  const m1 = canvas.getContext('2d');
  tGlob = 0;
  t1 = 0;
  t2 = 0;
  t3 = 0;
  y1 = 0;
  y2 = 0;
  y3 = 0;

  function letterMDrowing(x, y, color) {
    m1.beginPath();
    m1.lineWidth = 2;
    m1.strokeStyle = '#00000';
    m1.moveTo(x + 10, y + 30);
    m1.lineTo(x + 70, y + 30);
    m1.lineTo(x + 150, y + 120);
    m1.lineTo(x + 230, y + 30);
    m1.lineTo(x + 290, y + 30);
    m1.lineTo(x + 290, y + 140);
    m1.lineTo(x + 240, y + 140);
    m1.lineTo(x + 240, y + 60);
    m1.lineTo(x + 170, y + 140);
    m1.lineTo(x + 130, y + 140);
    m1.lineTo(x + 60, y + 60);
    m1.lineTo(x + 60, y + 140);
    m1.lineTo(x + 10, y + 140);
    m1.lineTo(x + 10, y + 30);
    m1.fillStyle = color;
    m1.fill();
    m1.stroke();
  }

  function letterIDrowing(x, y) {
    m1.beginPath();
    m1.lineWidth = 2;
    m1.strokeStyle = '#00000';
    m1.moveTo(x + 10, y + 30);
    m1.lineTo(x + 60, y + 30);
    m1.lineTo(x + 60, y + 115);
    m1.lineTo(x + 240, y + 30);
    m1.lineTo(x + 290, y + 30);
    m1.lineTo(x + 290, y + 140);
    m1.lineTo(x + 240, y + 140);
    m1.lineTo(x + 240, y + 60);
    m1.lineTo(x + 60, y + 140);
    m1.lineTo(x + 10, y + 140);
    m1.lineTo(x + 10, y + 30);
    m1.fillStyle = '#1EE91B';
    m1.fill();
    m1.stroke();
  }

  
  function firstMAnimation(x) {
    t1 += 1;
    y1 = 100 - 5 * t1 + (0.5 * t1 * t1) / 2;
    console.log("first");

    if (y1 > 100) {
      t1 = 0;
    }
    letterMDrowing(x, y1, "#FF0000");   
  }

  function iAnimation(x) {
    t2 += 1;
    y2 = 100 - 5 * t2 + (0.5 * t2 * t2) / 2;
    console.log("second");
    if (y2 > 100) {
      t2 = 0;
    }
    letterIDrowing(x, y2);
  }

  function secondMAnimation(x) {
    t3 += 1;
    y3 = 100 - 5 * t3 + (0.5 * t3 * t3) / 2;
    console.log("second");
    if (y3 > 100) {
      t3 = 0;
    }
    letterMDrowing(x, y3, "#0000FF");
  }

  function pictureAnimation() {
    m1.clearRect(0, 0, 1300, 400);
    console.log("clear");
    tGlob += 1;
    if (tGlob >= 0) {
      firstMAnimation(0);
    }
    if (tGlob >= 5) {
      iAnimation(500);
    }
    if (tGlob >= 10) {
      secondMAnimation(1000);
    }
  }

  setInterval(pictureAnimation, 25);
} 