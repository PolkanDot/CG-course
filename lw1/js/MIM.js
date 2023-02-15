window.onload = () => {
  const canvas = document.getElementById('Miftakhov');
  const m1 = canvas.getContext('2d');
  tGlob = 0;
  t1 = 0;
  t2 = 0;
  y1 = 0;
  y2 = 0;
  function M1() {
    m1.clearRect(0, 0, 800, 580);
    tGlob += 1;

    if (tGlob >= 0)
    {
      t1 += 1;
      y1 = 0 - 5 * t1 + (0.5 * t1 * t1) / 2;

      if (y1 > 0) {
        t1 = 0;
      }
      
      console.log("blyat");
      m1.beginPath();
      m1.lineWidth = 2;
      m1.strokeStyle = '#FFFFFF';
      m1.moveTo(10, y1 + 30);
      m1.lineTo(70, y1 + 30);
      m1.lineTo(150, y1 + 120);
      m1.lineTo(230, y1 + 30);
      m1.lineTo(290, y1 + 30);
      m1.lineTo(290, y1 + 140);
      m1.lineTo(240, y1 + 140);
      m1.lineTo(240, y1 + 60);
      m1.lineTo(170, y1 + 140);
      m1.lineTo(130, y1 + 140);
      m1.lineTo(60, y1 + 60);
      m1.lineTo(60, y1 + 140);
      m1.lineTo(10, y1 + 140);
      m1.lineTo(10, y1 + 30);
      m1.fillStyle = '#FF2041';
      m1.fill();
      m1.stroke();
    }      
    
    if (tGlob >= 10) 
    {
      t2 += 1;
      y2 = 0 - 5 * t2 + (0.5 * t2 * t2) / 2;
      if (y2 > 0) {
        t2 = 0;
      }

      console.log("hi");
      m1.beginPath();
      m1.lineWidth = 2;
      m1.strokeStyle = '#FFFFFF';
      m1.moveTo(510, y2 + 30);
      m1.lineTo(570, y2 + 30);
      m1.lineTo(650, y2 + 120);
      m1.lineTo(730, y2 + 30);
      m1.lineTo(790, y2 + 30);
      m1.lineTo(790, y2 + 140);
      m1.lineTo(740, y2 + 140);
      m1.lineTo(740, y2 + 60);
      m1.lineTo(670, y2 + 140);
      m1.lineTo(630, y2 + 140);
      m1.lineTo(560, y2 + 60);
      m1.lineTo(560, y2 + 140);
      m1.lineTo(510, y2 + 140);
      m1.lineTo(510, y2 + 30);
      m1.fillStyle = '#FF2041';
      m1.fill();
      m1.stroke();
    }    
  }
  setInterval(M1, 30);
} 