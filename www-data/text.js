function get_text_id() {
  const url = window.location.href;
  const pos = url.lastIndexOf("/");
  const id = url.substring(pos+1);
  return id;
}

function fetch_text_by_id(id) {
  return fetch("../api/v1/posts/" + id);
}

function setup_text() {
  const id = get_text_id();
  fetch_text_by_id(id)
    .then(function (response) {
      return response.text();
    })
    .then(function (text) {
      document.getElementById("text").innerHTML = text; // TODO: escape
    })
    .catch(function (error) {
      alert(error);
    });
}

setup_text();
