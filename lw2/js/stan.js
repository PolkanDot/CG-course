window.onload = () => {
	 const canvas = document.getElementById('Stan');
	 const ct1 = canvas.getContext('2d');

	// Pants
	ct1.fillStyle = '#4279C6';
	ct1.fillRect(25, 160, 80, 30);


	//Bots
	ct1.beginPath();
	ct1.lineWidth = 0.5;
	ct1.strokeStyle = '#000';
	ct1.moveTo(20, 190);
	ct1.bezierCurveTo(30, 185, 60, 185, 70, 190);
	ct1.lineTo(20, 190)
	ct1.fillStyle = '#000';
	ct1.stroke();
	ct1.fill();

	ct1.beginPath();
	ct1.strokeStyle = '#000';
	ct1.moveTo(65, 189);
	ct1.bezierCurveTo(70, 184, 110, 186, 115, 191);
	ct1.lineTo(65, 189)
	ct1.fillStyle = '#000';
	ct1.stroke();
	ct1.fill();

	// Jacket
	ct1.beginPath();
	ct1.strokeStyle = '#CF6D5F';
	ct1.moveTo(10, 160);
	ct1.bezierCurveTo(20, 80, 110, 80, 120, 160);
	ct1.lineTo(110, 160);
	ct1.lineTo(110, 170);
	ct1.bezierCurveTo(90, 180, 40, 180, 20, 170);
	ct1.lineTo(20, 160);
	ct1.lineTo(10, 160);
	ct1.fillStyle = '#CF6D5F';
	ct1.stroke();
	ct1.fill();

	ct1.beginPath();
	ct1.strokeStyle = '#000';
	ct1.moveTo(23, 160);
	ct1.lineTo(30, 140);
	ct1.moveTo(107, 160);
	ct1.lineTo(100, 140);
	ct1.stroke();
	
	ct1.beginPath();
	ct1.lineWidth = 1;
	ct1.moveTo(65, 177);
	ct1.lineTo(68, 120);
	ct1.stroke();

	ct1.beginPath();
	ct1.strokeStyle = '#313031';
	ct1.arc(60, 145, 1.5, 0 * Math.PI, 2 * Math.PI);
	ct1.fillStyle = '#313031';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.arc(59, 157, 1.5, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.arc(58, 169, 1.5, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();
	ct1.stroke();

	ct1.strokeStyle = '#FF2042';
	ct1.fillStyle = '#FF2042';
	
	ct1.beginPath();
	ct1.moveTo(25, 115);
	ct1.bezierCurveTo(20, 125, 70, 150, 65, 135);
	ct1.lineTo(25, 115);
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.moveTo(105, 120);
	ct1.bezierCurveTo(108, 130, 65, 150, 70, 135);
	ct1.lineTo(95, 115);
	ct1.fill();
	ct1.stroke();

	ct1.strokeStyle = '#000';
	ct1.lineWidth = 0.3;

	ct1.beginPath();
	ct1.arc(112, 162, 10, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();

	ct1.beginPath();
	ct1.arc(105, 159, 5, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.arc(18, 158, 10, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();

	ct1.beginPath();
	ct1.arc(25, 156, 5, 0 * Math.PI, 2 * Math.PI);
	ct1.fill();
	ct1.stroke();

	// Head
	ct1.beginPath();
	ct1.lineWidth = 1;
	ct1.strokeStyle = '#FFECC0';
	ct1.arc(64, 78, 55, 0 * Math.PI, 2 * Math.PI);
	ct1.fillStyle = '#FFECC0';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.lineWidth = 1;
	ct1.strokeStyle = '#3974C6';
	ct1.arc(64, 72, 57, 10.6 / 10 * Math.PI, 19.1 / 10 * Math.PI);
	ct1.fillStyle = '#3974C6';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.strokeStyle = '#FF2041';
	ct1.lineWidth = 1;
	ct1.arc(70, 250, 200, 27.82 / 20 * Math.PI, 31.65 / 20 * Math.PI);
	ct1.lineTo(121, 67);
	ct1.arc(70, 261, 200, 31.65 / 20 * Math.PI, 27.9 / 20 * Math.PI, true);
	ct1.lineTo(3, 62);
	ct1.fillStyle = '#FF2041';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.lineWidth = 2;
	ct1.strokeStyle = '#4A4142';
	ct1.moveTo(24, 69);
	ct1.lineTo(36, 57);
	ct1.moveTo(82, 56);
	ct1.lineTo(97, 65);
	ct1.stroke();

	ct1.beginPath();
	ct1.lineWidth = 2;
	ct1.strokeStyle = '#FF2042';
	ct1.moveTo(45, 22);
	ct1.lineTo(68, 8);
	ct1.moveTo(47, 24);
	ct1.lineTo(66, 6);
	ct1.moveTo(52, 28);
	ct1.lineTo(61, 3);
	ct1.moveTo(55, 29);
	ct1.lineTo(56, 2);
	ct1.moveTo(59, 28);
	ct1.lineTo(52, 3);
	ct1.moveTo(63, 26);
	ct1.lineTo(48, 6);
	ct1.moveTo(68, 22);
	ct1.lineTo(45, 10);
	ct1.moveTo(70, 17);
	ct1.lineTo(43, 14);
	ct1.moveTo(70, 14);
	ct1.lineTo(44, 18);
	ct1.stroke();

	ct1.beginPath();
	ct1.strokeStyle = '#FFF';
	ct1.moveTo(75, 65);
	ct1.bezierCurveTo(52, 72, 73, 110, 90, 95);
	ct1.bezierCurveTo(100, 80, 90, 65, 75, 65);
	ct1.fillStyle = '#FFF';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.lineWidth = 1;
	ct1.strokeStyle = '#313031';
	ct1.arc(72, 82, 1.5, 0 * Math.PI, 2 * Math.PI);
	ct1.fillStyle = '#313031';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.strokeStyle = '#FFF';
	ct1.moveTo(49, 65);
	ct1.bezierCurveTo(34, 65, 24, 80, 34, 95);
	ct1.bezierCurveTo(51, 110, 72, 72, 49, 65);
	ct1.fillStyle = '#FFF';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.lineWidth = 1;
	ct1.strokeStyle = '#313031';
	ct1.arc(50, 82, 1.5, 0 * Math.PI, 2 * Math.PI);
	ct1.fillStyle = '#313031';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.strokeStyle = '#000';
	ct1.moveTo(50, 110);
	ct1.bezierCurveTo(48, 113, 70, 125, 69, 120);
	ct1.bezierCurveTo(71, 118, 82, 114, 83, 110);
	ct1.bezierCurveTo(83, 107, 50, 108, 50, 110);
	ct1.fillStyle = '#000';
	ct1.fill();
	ct1.stroke();

	ct1.beginPath();
	ct1.moveTo(53, 110);
	ct1.lineTo(55, 115);
	ct1.lineTo(60, 115);
	ct1.lineTo(60, 109);
	ct1.lineTo(53, 110);
	ct1.fillStyle = '#FFF';
	ct1.fill();

	ct1.beginPath();
	ct1.moveTo(61, 109);
	ct1.lineTo(61, 115);
	ct1.lineTo(67, 114);
	ct1.lineTo(67, 109);
	ct1.lineTo(61, 109);
	ct1.fill();

	ct1.beginPath();
	ct1.moveTo(68, 109);
	ct1.lineTo(68, 114);
	ct1.lineTo(74, 114);
	ct1.lineTo(76, 109);
	ct1.lineTo(68, 109);
	ct1.fill();

	ct1.beginPath();
	ct1.moveTo(77, 109);
	ct1.lineTo(75, 114);
	ct1.lineTo(79, 114);
	ct1.lineTo(82, 109);
	ct1.lineTo(77, 109);
	ct1.fill();

	
} 