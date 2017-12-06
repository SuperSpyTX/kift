/* prelude.js Javascript's missing prelude */

function $(a) {
	if (/^f/.test(typeof a)) {
		document.addEventListener("DOMContentLoaded", a);	
	} else {
		return document[{
		'#': "getElementById",
		'.': "getElementsByClassName",
		'@': "getElementsByName",
		'=': "getElementsByTagName",
		$: "createElement"}[a[0]]
		|| 'querySelectorAll'](a.slice(1));
	}
};

/* Returns an object where obj[cookiename] == cookievalue */
$.cookies = function(r,c,i) {
	r = document.cookie.split(/ ;| ,|=/);
	c = {};
	for (i=0;++i < r.length;) {
		c[r[i - 1]] = r[i];
	}
	return c;
};

/* Takes a cookie name, Returns a cookie or null */
$.cookie = function (n) {
	n = document.cookie.match(RegExp('(?:^|;\\s*)' + n + '=([^;]*)'));
	return n ? n[1] : null;
};

/*
** Retrieve a network resource. Takes (type, url, callback), 
** the callback is passed the response.
*/

$.get = function(t,u,c,r) {
	r = new XMLHttpRequest();
	r.open("GET", u);
	r.responseType = t;
	r.onreadystatechange = function() {
		if (r.readyState==4) {
			c(t=="json"&&r.responseType!==t ? JSON.parse(r.response) : r.response);
	}};
	r.send();
};

/*
** Post to a URL, Takes (data, type, url, callback)
** Callback is optional. 
*/

$.post = function(d,t,u,c,r) {
	r = new XMLHttpRequest();
	r.open("POST", u, true);
	r.setRequestHeader("Content-type", t);
	r.onreadystatechange = function() {
	if(r.readyState == XMLHttpRequest.DONE && r.status == 200) {c()}};
	r.send(d);
};
