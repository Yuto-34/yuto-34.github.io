function psy() {
	var element = document.getElementById('howmuch');
	var number = element.value;
	txtData = document.getElementById('txt_data').value.replace(/\r?\n/g, '%0D%0A');
	address00 = document.getElementById('your_address').value;
	address01 = 'edu.cc.uec.ac.jp';
	address0 = address00 + address01;
	address00 = address00.slice(1);
	address1 = 'hisano';
	address2 = '@bunka.uec.ac.jp';
	address3 = 'hisano.report';
	address4 = '@gmail.com';
	address = address1 + address2 + ',' + address3 + address4;
	subject = '31-' + address00 + '-' + number;
	body = address00 + document.getElementById('your_name').value + '%0D%0A' + txtData;
	location.href = 'mailto:' + address + '?cc=' + address0 + '&subject=' + subject + '&body=' + body;
};

function na() {
	var element2 = document.getElementById('howmuch2');
	var number2 = element2.value;
	txtData2 = document.getElementById('txt_data2').value.replace(/\r?\n/g, '%0D%0A');
	address100 = document.getElementById('your_address12').value;
	address101 = 'edu.cc.uec.ac.jp';
	address10 = address100 + address101;
	address100 = address100.slice(1);
	address11 = 'nu2analysis';
	address12 = '@mt.mce.uec.ac.jp';
	address13 = address11 + address12;
	subject2 = number2 + ' ' + address100 + ' ' + document.getElementById('your_name2').value;
	body2 = address100 + document.getElementById('your_name2').value + '%0D%0A' + txtData2;
	location.href = 'mailto:' + address1 + '?cc=' + address10 + '&subject=' + subject + '&body=' + body;
};