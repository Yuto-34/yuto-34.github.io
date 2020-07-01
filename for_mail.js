function psy() {
	var element = document.getElementById('howmuch');
	var number = element.value;
	txtData = document.getElementById('txt_data').value.replace(/\r?\n/g, '%0D%0A');
	address00 = document.getElementById('your_address').value;
	address01 = '@edu.cc.uec.ac.jp';
	address0 = address00 + address01;
	address00 = address00.slice(1);
	address1 = 'hisano';
	address2 = '@bunka.uec.ac.jp';
	address3 = 'hisano.report';
	address4 = '@gmail.com';
	addressb = document.getElementById('bcc').value;
	address = address1 + address2 + ',' + address3 + address4;
	subject = '31-' + address00 + '-' + number;
	body = address00 + document.getElementById('your_name').value + '%0D%0A' + txtData;
	location.href = 'mailto:' + address + '?cc=' + address0 + '&bcc=' + addressb + '&subject=' + subject + '&body=' + body;
};

function na() {
	var elements = document.getElementById('howmuch2');
	var numbers = elements.value;
	txtDatas = document.getElementById('txt_data2').value.replace(/\r?\n/g, '%0D%0A');
	address00s = document.getElementById('your_address2').value;
	address01s = '@edu.cc.uec.ac.jp';
	address0s = address00s + address01s;
	address00s = address00s.slice(1);
	address1s = 'nu2analysis';
	address2s = '@mt.mce.uec.ac.jp';
	addressbcc = document.getElementById('bcc2').value;
	addresss = address1s + address2s;
	subjects = numbers + ' ' + address00s + ' ' + document.getElementById('your_name2').value ;
	bodys = address00s + document.getElementById('your_name2').value + '%0D%0A' + txtDatas;
	location.href = 'mailto:' + addresss + '?cc=' + address0s + '&bcc=' + addressbcc + '&subject=' + subjects + '&body=' + bodys;
};