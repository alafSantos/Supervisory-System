function checkUser()
{
	var username = document.login.username.value, password = document.login.password.value, done = 0;
	username=username.toLowerCase();
	password=password.toLowerCase();
	if (username=="alaf" && password=="12345678")
	{
		window.location="page2.html"; 
		done=1;
	}
	if (username=="lucas" && password=="abcdefgh")
	{
		window.location="page2.html"; 
		done=1;
	}
	if (username=="joao" && password=="qwertyui")
	{
		window.location="page2.html"; 
		done=1;
	}
	if (done==0)
		alert("error: try again");
}

function noEnter(objEvent) 
{
	var iKeyCode = objEvent.keyCode;
	if(iKeyCode == 13) return false;
	else return true;
}