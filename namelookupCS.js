// JavaScript for Marvel Character Lookup
// Ryan Schultz, Kenyon College, 2019
var searchType;  // Save serach type here

$(document).ready(function () {
    console.log("start!");
    searchType="Year";
    $("#search-btn").click(getMatches);

    $("#clear").click(clearResults);

    $(".dropdown-menu li a").click(function(){
	console.log("pick!"+$(this).text());
	/*Sets the text of "dropdown-menu li a" to the text of the class "selection" (Year) within "dropdown-menue li a"'s parent class "btn-group"*/
	$(this).parents(".btn-group").find('.selection').text($(this).text());
	/*Assigns the text of this "dropdown-menu li a" to the variable searchType.*/
	searchType=$(this).text();
    });

});

// Build output table of character names from comma delimited list
function nameTable(list) {
    var result = "<div id='newTable'><table class='w3-table-all w3-hoverable' border='2'><tr><th colspan='4'>Name</th><tr>";
    //a is an array
	var a = list.split(",");
    var aLen = a.length;
    for (var i = 0; i < aLen; i+=48) {
	result += "<tr><td>"+a[i]+"</td><td>"+a[i+12]+"</td><td>"+a[i+24]+"</td><td>"+a[i+36]+"</td></tr>";
    }
    result += "</table></div id='newTable'>";

    return result;
	
	$("#newTable").on("click", "td", processInfo(results), function() {
		console.log("Clicked!");
	});

}

//Builds output table of character data from comma delimited list
function characterData(list){
	var result = '<table class="w3-table-all w3-hoverable" border="2"><tr><th>Name</th><th>Identity</th><th>Alignment</th><th>Eye Color</th><th>Hair Color</th><th>Sex</th><th>Sexual Orientation</th><th>Living Status</th><th>Number of Appearances</th><th>First Appearance</th><th>Webpage</th><tr>';
	var a = list.split(",");
	var aLen = a.length;
	for(var i = 0; i < aLen; i+=12)
	{
		var name = a[i];
		var index = a.indexOf(name);
		result += "<tr>";
		for(index; index < index+12; index++)
		{
			result += "<td>a[index]</td>"
		}
		result += "</tr>";
	}
	result += "</table>";
}


function processInfo(results){
	console.log("Get info");
	$('#searchresults').empty();
	console.log("still getting	info");
	$('#searchresults').append(characterData(results));
	console.log("still getting	info");
}


function processResults(results) {
    $('#searchresults').empty();
    $('#searchresults').append(nameTable(results));

}

function clearResults() {
    $('#searchresults').empty();
}

function getMatches(){
    if ($('#search').val().length < 2) return;
    $('#searchresults').empty();
    $.ajax({
		url: '/cgi-bin/schultz4_character_lookup.cgi?name='+$('#search').val()+'&type_select='+searchType,
		dataType: 'text',
		success: processResults,
		error: function(){alert("Error: Something went wrong");}
    });

}
