window.onload = () => {
  const canvas = document.getElementById('Miftakhov');
  const ct = canvas.getContext('2d');
  t = 0;
  y = 0;
  function M() {
    ct.clearRect(5, y - 20, 295, y + 200);
    t += 1;
    y = 0 - 5 * t + (0.5 * t * t) / 2
    if (y > 0) {
      t = 0;
    }
    ct.beginPath();
    ct.lineWidth = 2;
    ct.strokeStyle = '#FFFFFF';
    ct.moveTo(10, y + 10);
    ct.lineTo(70, y + 10);
    ct.lineTo(150, y + 110);
    ct.lineTo(230, y + 10);
    ct.lineTo(290, y + 10);
    ct.lineTo(290, y + 140);
    ct.lineTo(240, y + 140);
    ct.lineTo(240, y + 50);
    ct.lineTo(170, y + 140);
    ct.lineTo(130, y + 140);
    ct.lineTo(60, y + 50);
    ct.lineTo(60, y + 140);
    ct.lineTo(10, y + 140);
    ct.lineTo(10, y + 10);
    ct.fillStyle = '#FF2041';
    ct.fill();
    ct.stroke();
  }

  setInterval(M, 160);
} 