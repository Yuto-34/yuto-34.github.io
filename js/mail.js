function psy() {
	var number = document.getElementById('howmuch').value;
	txtData = document.getElementById('txt_data').value.replace(/\r?\n/g, '%0D%0A');
	student_number = document.getElementById('your_address').value;
	student_name = document.getElementById('your_name').value
	uec_domain = '@edu.cc.uec.ac.jp';
	student_address = student_number + uec_domain;
	student_number = student_number.slice(1);
	address1 = 'hisano@bunka.uec.ac.jp';
	address2 = 'hisano.report@gmail.com';
	address = address1 + ',' + address2;
	private_address = document.getElementById('bcc').value;
	subject = '31-' + student_number + '-' + number;
	body = number + '回目授業レポート' + student_number + student_name + '%0D%0A' + '%0D%0A' + txtData;
	location.href = 'mailto:' + address + '?cc=' + student_address + '&bcc=' + private_address + '&subject=' + subject + '&body=' + body;
};

function na() {
	var numbers = document.getElementById('howmuch2').value;
	txtDatas = document.getElementById('txt_data2').value.replace(/\r?\n/g, '%0D%0A');
	student_number = document.getElementById('your_address').value;
	student_name = document.getElementById('your_name').value;
	uec_domain = '@edu.cc.uec.ac.jp';
	student_address = student_number + uec_domain;
	student_number = student_number.slice(1);
	teacher_address = 'nu2analysis@mt.mce.uec.ac.jp';
	private_address = document.getElementById('bcc').value;
	subjects = numbers + ' ' + student_number + ' ' + student_name ;
	bodys = student_number + student_name + '%0D%0A' + '%0D%0A' + txtDatas;
	location.href = 'mailto:' + teacher_address + '?cc=' + student_address + '&bcc=' + private_address + '&subject=' + subjects + '&body=' + bodys;
};

function na_handin() {
	var numbers = document.getElementById('howmuch3').value;
	txtDatas = document.getElementById('txt_data3').value.replace(/\r?\n/g, '%0D%0A');
	student_number = document.getElementById('your_address').value;
	student_name = document.getElementById('your_name').value;
	var version = document.getElementById('hand_in').value;
	uec_domain = '@edu.cc.uec.ac.jp';
	student_address = student_number + uec_domain;
	student_number = student_number.slice(1);
	teacher_address = 'nu2analysis@mt.mce.uec.ac.jp';
	private_address = document.getElementById('bcc').value;
	subjects = numbers + version + ' ' + student_number + ' ' + student_name ;
	bodys = student_number + student_name + '%0D%0A' + '%0D%0A' + txtDatas;
	location.href = 'mailto:' + teacher_address + '?cc=' + student_address + '&bcc=' + private_address + '&subject=' + subjects + '&body=' + bodys;
};