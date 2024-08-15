fetch("../api/v1/latest")
	.then(function (response) {
		return response.json();
	})
	.then(function (json) {
		latest_html = "";
		for (const item in json.items) {
			latest_html += "<p>author: " + item["author"] + "</p>";
		}
		document.getElementById("latest").innerHTML = latest_html;
	})
	.catch(function (error) {
		alert(error);
	});

function onSend() {
	const author = document.forms["form"].author.value;
	const text =   document.forms["form"].text.value;

	fetch("../api/v1/posts?author=" + author, {
		method: "POST",
		body: text,
	})
	.then(function(response) {
		return response.json();
	})
	.then(function(json) {
		alert(json);
	})
	.catch(function (error) {
		alert(error);
	});
}
