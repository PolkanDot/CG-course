window.onload = () => {
	 const canvas = document.getElementById('Stan');
	 const ct1 = canvas.getContext('2d');

	function pants(x, y)
	{
		ct1.fillStyle = '#4279C6';
		ct1.fillRect(x + 25, y + 160, 80, 30);
	}
	
	function boots(x, y)
	{
		ct1.beginPath();
		ct1.lineWidth = 0.5;
		ct1.strokeStyle = '#000';
		ct1.moveTo(x + 20, y + 190);
		ct1.bezierCurveTo(x + 30, y + 185, x + 60, y + 185, x + 70, y + 190);
		ct1.lineTo(x + 20, y + 190)
		ct1.fillStyle = '#000';
		ct1.stroke();
		ct1.fill();

		ct1.beginPath();
		ct1.strokeStyle = '#000';
		ct1.moveTo(x + 65, y + 189);
		ct1.bezierCurveTo(x + 70, y + 184, x + 110, y + 186, x + 115, y + 191);
		ct1.lineTo(x + 65, y + 189)
		ct1.fillStyle = '#000';
		ct1.stroke();
		ct1.fill();
	}

	function jacket(x, y) 
	{
		ct1.beginPath();
		ct1.strokeStyle = '#CF6D5F';
		ct1.moveTo(x + 10, y + 160);
		ct1.bezierCurveTo(x + 20, y + 80, x + 110, y + 80, x + 120, y + 160);
		ct1.lineTo(x + 110, y + 160);
		ct1.lineTo(x + 110, y + 170);
		ct1.bezierCurveTo(x + 90, y + 180, x + 40, y + 180, x + 20, y + 170);
		ct1.lineTo(x + 20, y + 160);
		ct1.lineTo(x + 10, y + 160);
		ct1.fillStyle = '#CF6D5F';
		ct1.stroke();
		ct1.fill();

		ct1.beginPath();
		ct1.strokeStyle = '#000';
		ct1.moveTo(x + 23, y + 160);
		ct1.lineTo(x + 30, y + 140);
		ct1.moveTo(x + 107, y + 160);
		ct1.lineTo(x + 100, y + 140);
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 1;
		ct1.moveTo(x + 65, y + 177);
		ct1.lineTo(x + 68, y + 120);
		ct1.stroke();

		ct1.beginPath();
		ct1.strokeStyle = '#313031';
		ct1.arc(x + 60, y + 145, 1.5, 0 * Math.PI, 2 * Math.PI);
		ct1.fillStyle = '#313031';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.arc(x + 59, y + 157, 1.5, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.arc(x + 58, y + 169, 1.5, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();
		ct1.stroke();

		ct1.strokeStyle = '#FF2042';
		ct1.fillStyle = '#FF2042';

		ct1.beginPath();
		ct1.moveTo(x + 25, y + 115);
		ct1.bezierCurveTo(x + 20, y + 125, x + 70, y + 150, x + 65, y + 135);
		ct1.lineTo(x + 25, y + 115);
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.moveTo(x + 105, y + 120);
		ct1.bezierCurveTo(x + 108, y + 130, x + 65, y + 150, x + 70, y + 135);
		ct1.lineTo(x + 95, y + 115);
		ct1.fill();
		ct1.stroke();

		ct1.strokeStyle = '#000';
		ct1.lineWidth = 0.3;

		ct1.beginPath();
		ct1.arc(x + 112, y + 162, 10, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();

		ct1.beginPath();
		ct1.arc(x + 105, y + 159, 5, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.arc(x + 18, y + 158, 10, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();

		ct1.beginPath();
		ct1.arc(x + 25, y + 156, 5, 0 * Math.PI, 2 * Math.PI);
		ct1.fill();
		ct1.stroke();
	}
	
	function head(x, y) 
	{
		ct1.beginPath();
		ct1.lineWidth = 1;
		ct1.strokeStyle = '#FFECC0';
		ct1.arc(x + 64, y + 78, 55, 0 * Math.PI, 2 * Math.PI);
		ct1.fillStyle = '#FFECC0';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 1;
		ct1.strokeStyle = '#3974C6';
		ct1.arc(x + 64, y + 72, 57, 10.6 / 10 * Math.PI, 19.1 / 10 * Math.PI);
		ct1.fillStyle = '#3974C6';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.strokeStyle = '#FF2041';
		ct1.lineWidth = 1;
		ct1.arc(x + 70, y + 250, 200, 27.82 / 20 * Math.PI, 31.65 / 20 * Math.PI);
		ct1.lineTo(x + 121, y + 67);
		ct1.arc(x + 70, y + 261, 200, 31.65 / 20 * Math.PI, 27.9 / 20 * Math.PI, true);
		ct1.lineTo(x + 3, y + 62);
		ct1.fillStyle = '#FF2041';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 2;
		ct1.strokeStyle = '#4A4142';
		ct1.moveTo(x + 24, y + 69);
		ct1.lineTo(x + 36, y + 57);
		ct1.moveTo(x + 82, y + 56);
		ct1.lineTo(x + 97, y + 65);
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 2;
		ct1.strokeStyle = '#FF2042';
		ct1.moveTo(x + 45, y + 22);
		ct1.lineTo(x + 68, y + 8);
		ct1.moveTo(x + 47, y + 24);
		ct1.lineTo(x + 66, y + 6);
		ct1.moveTo(x + 52, y + 28);
		ct1.lineTo(x + 61, y + 3);
		ct1.moveTo(x + 55, y + 29);
		ct1.lineTo(x + 56, y + 2);
		ct1.moveTo(x + 59, y + 28);
		ct1.lineTo(x + 52, y + 3);
		ct1.moveTo(x + 63, y + 26);
		ct1.lineTo(x + 48, y + 6);
		ct1.moveTo(x + 68, y + 22);
		ct1.lineTo(x + 45, y + 10);
		ct1.moveTo(x + 70, y + 17);
		ct1.lineTo(x + 43, y + 14);
		ct1.moveTo(x + 70, y + 14);
		ct1.lineTo(x + 44, y + 18);
		ct1.stroke();

		ct1.beginPath();
		ct1.strokeStyle = '#FFF';
		ct1.moveTo(x + 75, y + 65);
		ct1.bezierCurveTo(x + 52, y + 72, x + 73, y + 110, x + 90, y + 95);
		ct1.bezierCurveTo(x + 100, y + 80, x + 90, y + 65, x + 75, y + 65);
		ct1.fillStyle = '#FFF';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 1;
		ct1.strokeStyle = '#313031';
		ct1.arc(x + 72, y + 82, 1.5, 0 * Math.PI, 2 * Math.PI);
		ct1.fillStyle = '#313031';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.strokeStyle = '#FFF';
		ct1.moveTo(x + 49, y + 65);
		ct1.bezierCurveTo(x + 34, y + 65, x + 24, y + 80, x + 34, y + 95);
		ct1.bezierCurveTo(x + 51, y + 110, x + 72, y + 72, x + 49, y + 65);
		ct1.fillStyle = '#FFF';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.lineWidth = 1;
		ct1.strokeStyle = '#313031';
		ct1.arc(x + 50, y + 82, 1.5, 0 * Math.PI, 2 * Math.PI);
		ct1.fillStyle = '#313031';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.strokeStyle = '#000';
		ct1.moveTo(x + 50, y + 110);
		ct1.bezierCurveTo(x + 48, y + 113, x + 70, y + 125, x + 69, y + 120);
		ct1.bezierCurveTo(x + 71, y + 118, x + 82, y + 114, x + 83, y + 110);
		ct1.bezierCurveTo(x + 83, y + 107, x + 50, y + 108, x + 50, y + 110);
		ct1.fillStyle = '#000';
		ct1.fill();
		ct1.stroke();

		ct1.beginPath();
		ct1.moveTo(x + 53, y + 110);
		ct1.lineTo(x + 55, y + 115);
		ct1.lineTo(x + 60, y + 115);
		ct1.lineTo(x + 60, y + 109);
		ct1.lineTo(x + 53, y + 110);
		ct1.fillStyle = '#FFF';
		ct1.fill();

		ct1.beginPath();
		ct1.moveTo(x + 61, y + 109);
		ct1.lineTo(x + 61, y + 115);
		ct1.lineTo(x + 67, y + 114);
		ct1.lineTo(x + 67, y + 109);
		ct1.lineTo(x + 61, y + 109);
		ct1.fill();

		ct1.beginPath();
		ct1.moveTo(x + 68, y + 109);
		ct1.lineTo(x + 68, y + 114);
		ct1.lineTo(x + 74, y + 114);
		ct1.lineTo(x + 76, y + 109);
		ct1.lineTo(x + 68, y + 109);
		ct1.fill();

		ct1.beginPath();
		ct1.moveTo(x + 77, y + 109);
		ct1.lineTo(x + 75, y + 114);
		ct1.lineTo(x + 79, y + 114);
		ct1.lineTo(x + 82, y + 109);
		ct1.lineTo(x + 77, y + 109);
		ct1.fill();
	}

	function stanDrowing(mainX, mainY)
	{
		pants(mainX, mainY);
		boots(mainX, mainY);
		jacket(mainX, mainY);
		head(mainX, mainY);		
	}

	stanDrowing(400, 200);
} 