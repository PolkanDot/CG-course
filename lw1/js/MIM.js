window.onload = () => {
	 const canvas = document.getElementById('Stan');
	 const ctx = canvas.getContext('2d');
   const grd = ctx.createLinearGradient(0, 0, 200, 0);

  grd.addColorStop(0, "red");

  grd.addColorStop(1, "white");

  // Fill with gradient

  ctx.fillStyle = grd;

  ctx.fillRect(10, 10, 150, 80);
} 