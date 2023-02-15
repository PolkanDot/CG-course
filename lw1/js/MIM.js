window.onload = () => {
  const canvas = document.getElementById('Miftakhov');
  const m1 = canvas.getContext('2d');
  tGlob = 0;
  t1 = 0;
  t2 = 0;
  t3 = 0;
  y1 = 0;
  y2 = 0;
  y3 = 0;
  function M1() {
    m1.clearRect(0, 0, 1300, 400);
    tGlob += 1;

    if (tGlob >= 0)
    {
      t1 += 1;
      y1 = 100 - 5 * t1 + (0.5 * t1 * t1) / 2;

      if (y1 > 100) {
        t1 = 0;
      }
      
      m1.beginPath();
      m1.lineWidth = 2;
      m1.strokeStyle = '#00000';
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

    if (tGlob >= 5) {
      t2 += 1;
      y2 = 100 - 5 * t2 + (0.5 * t2 * t2) / 2;
      if (y2 > 100) {
        t2 = 0;
      }

      m1.beginPath();
      m1.lineWidth = 2;
      m1.strokeStyle = '#00000';
      m1.moveTo(510, y2 + 30);
      m1.lineTo(560, y2 + 30);
      m1.lineTo(560, y2 + 115);
      m1.lineTo(740, y2 + 30);
      m1.lineTo(790, y2 + 30);
      m1.lineTo(790, y2 + 140);
      m1.lineTo(740, y2 + 140);
      m1.lineTo(740, y2 + 60);
      m1.lineTo(560, y2 + 140);
      m1.lineTo(510, y2 + 140);
      m1.lineTo(510, y2 + 30);
      m1.fillStyle = '#1EE91B';
      m1.fill();
      m1.stroke();
    }
    
    if (tGlob >= 10) 
    {
      t3 += 1;
      y3 = 100 - 5 * t3 + (0.5 * t3 * t3) / 2;
      if (y3 > 100) {
        t3 = 0;
      }

      m1.beginPath();
      m1.lineWidth = 2;
      m1.strokeStyle = '#00000';
      m1.moveTo(1010, y3 + 30);
      m1.lineTo(1070, y3 + 30);
      m1.lineTo(1150, y3 + 120);
      m1.lineTo(1230, y3 + 30);
      m1.lineTo(1290, y3 + 30);
      m1.lineTo(1290, y3 + 140);
      m1.lineTo(1240, y3 + 140);
      m1.lineTo(1240, y3 + 60);
      m1.lineTo(1170, y3 + 140);
      m1.lineTo(1130, y3 + 140);
      m1.lineTo(1060, y3 + 60);
      m1.lineTo(1060, y3 + 140);
      m1.lineTo(1010, y3 + 140);
      m1.lineTo(1010, y3 + 30);
      m1.fillStyle = '#0000FF';
      m1.fill();
      m1.stroke();
    }    


  }
  setInterval(M1, 30);
} 