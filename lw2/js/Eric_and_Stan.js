window.onload = () => {
	 const canvas = document.getElementById('Stan');
	 const ct1 = canvas.getContext('2d');

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

} 