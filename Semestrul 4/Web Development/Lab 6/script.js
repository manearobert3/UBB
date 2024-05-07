var array = [
  { name: "Andrei", grade: 9, year: 2, age: 25 },
  { name: "Maria", grade: 8, year: 3, age: 30 },
  { name: "John", grade: 7, year: 1, age: 22 },
  { name: "Elena", grade: 10, year: 2, age: 28 },
  { name: "Alex", grade: 8, year: 2, age: 26 },
  { name: "Sophia", grade: 9, year: 3, age: 32 },
  { name: "Michael", grade: 7, year: 2, age: 24 },
  { name: "Emma", grade: 10, year: 1, age: 20 },
  { name: "David", grade: 8, year: 2, age: 29 },
  { name: "Olivia", grade: 9, year: 1, age: 23 },
];
// $(document).ready(function () {
//   buildTable(array);
// });

$("th").on("click", function () {
  var column = $(this).data("column");
  var order = $(this).data("order");
  var dataType = typeof array[0][column];
  console.log("column was clicked: ", column, order);
  console.log("dataType: ", dataType);
  if (order == "desc") {
    $(this).data("order", "asc");
    if (dataType === "string") {
      array = array.sort((a, b) => (a[column] > b[column] ? 1 : -1));
    } else if (dataType === "number") {
      array = array.sort((a, b) => a[column] - b[column]);
    }
  } else {
    $(this).data("order", "desc");
    if (dataType === "string") {
      array = array.sort((a, b) => (a[column] < b[column] ? 1 : -1));
    } else if (dataType === "number") {
      array = array.sort((a, b) => b[column] - a[column]);
    }
  }
  buildTable(array);
});

$("td").on("click", function () {
  var column = $(this).data("column");

  var nextColumn = column + 1;
  if (nextColumn === 5) {
    nextColumn = 1;
  }
  console.log("footer was clicked!", column);
  $("#tableBody tr").each(function () {
    var col2 = $(this).find("td:eq(" + (column - 1) + ")");
    var col3 = $(this).find("td:eq(" + (nextColumn - 1) + ")");

    var temp = col2.text();
    col2.text(col3.text());
    col3.text(temp);
  });
  var headerCol = $("#tableMain th:eq(" + (column - 1) + ")");
  var nextHeaderCol = $("#tableMain th:eq(" + (nextColumn - 1) + ")");
  var tempHeader = headerCol.text();
  headerCol.text(nextHeaderCol.text());
  nextHeaderCol.text(tempHeader);
});

function buildTable(data) {
  var table = document.getElementById("tableBody");
  table.innerHTML = "";
  for (var i = 0; i < data.length; i++) {
    var row = `<tr>
      <td>${data[i].name}</td>
      <td>${data[i].grade}</td>
      <td>${data[i].year}</td>
      <td>${data[i].age}</td>
    </tr>`;

    table.innerHTML += row;
  }
}
