//	Max amount of nodes
var MAXNODES = 5;

//	last Command, subChoice, and ElementNum
var lCommand = 13;
var lSubChoice = -1;
var lElementNum = -1;

//	current pointer/value array
var ptArray = [1, 2, -1, -1, -1];
var valArray = [17, 14, 8, -1, -1];

//	For graphics: Keeps track
//	of nodes on top
var onScreen = [];

//	Old pointer/value array
var oPtArray = [-1, -1, -1, -1, -1];
var oValArray = [-1, -1, -1, -1, -1];

//	Current Pointers
var F = 0;
var R = 2;
var S = 0;
var pointP = 0;

//	old Pointers
var oF = -1;
var oS = -1;
var oR = -1;
var oldPointP = -1;

//	Error flags
var sFlag = false;
var infFlag = false;
var fFlag = false;
var undoFlag = false;

//	y-axis placement for graphics
var y_node = 110;
var y_nodeBot = 250;
var y_pointer = 70;
var y_pointerBot = 210;
var y_sidePointer = 20;
var y_nullBox = 130;

//	Create default graphics
window.onload = function () {
	$.getScript('objectCreation.js', function () {
		//test();
		
		createDownPointer(60, 70, "F");
		createDownPointer(85, 70, "T");
		createDownPointer(110, 70, "P");
		createDownPointer(435, 70, "R");
		createNodeTop(50, 110, valArray[0]);
		createNodeTop(200, 110, valArray[1]);
		createNodeTop(350, 110, valArray[2]);
		createNullBox(500, y_nullBox);
		
	});
}

//	Convert string to Bool
function stringToBool(s)
{
        if (s == 'true')
                return true;
        else
                return false;
}

//	Convert string back to array
//	Example string '17,14,08,-1,-1'
function stringToArray(s, num)
{
	var i;
	var count = 1;
	var temp = "";

	if (num == 1){
		temp = temp.concat(s[0]);
		temp = temp.concat(s[1]);
		ptArray[0] = parseInt(temp);
	        for (i=2; i<s.length; i++){
        	        if (s[i] == ','){
				temp = "";
				temp = temp.concat(s[i+1]);
				temp = temp.concat(s[i+2]);
				ptArray[count] = parseInt(temp);
				count++;
        	        }
       		 }
	}
	else if (num == 2){
		temp = temp.concat(s[0]);
                temp = temp.concat(s[1]);
                valArray[0] = parseInt(temp);
                for (i=2; i<s.length; i++){
                        if (s[i] == ','){
				temp = "";
                                temp = temp.concat(s[i+1]);
                                temp = temp.concat(s[i+2]);
                                valArray[count] = parseInt(temp);
				count++;
                        }
                 }
	}
	else if (num == 3){
		temp = temp.concat(s[0]);
                temp = temp.concat(s[1]);
                oPtArray[0] = parseInt(temp);
                for (i=2; i<s.length; i++){
                        if (s[i] == ','){
				temp = "";
                                temp = temp.concat(s[i+1]);
                                temp = temp.concat(s[i+2]);
                                oPtArray[count] = parseInt(temp);
				count++;
                        }
                 }
        }
	else if (num == 4){
		temp = temp.concat(s[0]);
                temp = temp.concat(s[1]);
                oValArray[0] = parseInt(temp);
                for (i=2; i<s.length; i++){
                        if (s[i] == ','){
				temp = "";
                                temp = temp.concat(s[i+1]);
                                temp = temp.concat(s[i+2]);
                                oValArray[count] = parseInt(temp);
				count++;
                        }
                 }
        }


}

//	Converts an array to string for json
//	Example string: '17,14,08,-1,-1'
function arrayToString(arr)
{
	var i;
	var stringArray = "";

	if (arr[0].toString().length == 1){
		stringArray = stringArray.concat('0');
                stringArray = stringArray.concat(arr[0]);
	}
	else{
                stringArray = stringArray.concat(arr[0]);
	}

	for (i=1; i<arr.length; i++){

		if (arr[i].toString().length == 1){
			stringArray = stringArray.concat(',0');
			stringArray = stringArray.concat(arr[i]);
		}
		else if (arr[i].toString().length == 2){
			stringArray = stringArray.concat(',');
	                stringArray = stringArray.concat(arr[i]);
		}
	}
	return stringArray;
	
}

//	Update all info passed back from cgi
function updateAll(data)
{
        lCommand = parseInt(data.lc);
        lSubChoice = parseInt(data.lsc);
        lElementNum = parseInt(data.len);
        stringToArray(data.pa, 1);
        stringToArray(data.va, 2);
        stringToArray(data.opa, 3);
        stringToArray(data.ova, 4);
        F = parseInt(data.f);
        R = parseInt(data.r);
        S = parseInt(data.s);
        pointP = parseInt(data.pointP);
        oF = parseInt(data.of);
        oS = parseInt(data.os);
        oR = parseInt(data.or);
        oldPointP = parseInt(data.opointP);
        sFlag = stringToBool(data.sf);
        infFlag = stringToBool(data.ilf);
        fFlag = stringToBool(data.ff);
        undoFlag = stringToBool(data.uef);
}

//--------------------------------------------------------------------

//	Calculate distance for graphics for
//	node placement and null placement
function calcDistance (numNode, type) {
        var dist = 150;

        if (numNode == undefined)
                return 0;

        if (type == 'pointer')
                return (numNode * dist + 50);
        if (type == 'nullBox')
                return (numNode * dist + 40);

        return (numNode * dist + 35);
}

//	Graphics for all nodes connected to Front pointer
//	and are after Front
function graphicsTopNodes() {
        $.getScript('objectCreation.js', function () {
                var i;
                var j;
                var xPosition;
                var nodeNum = 0;
                var temp = F;

                if (F != -1 && F != -2){
                        xPosition = calcDistance(nodeNum);
                        createDownPointer(xPosition+10, y_pointer, "F");
                        while (temp != -1 && temp != -2){
                                xPosition = calcDistance(nodeNum);
                                createNodeTop(xPosition, y_node, valArray[temp]);
                                onScreen.push(temp);
                                if (R == temp)
                                        createDownPointer(xPosition+85, y_pointer, "R");
                                if (S == temp)
                                        createDownPointer(xPosition+35, y_pointer, "T");
                                if (pointP == temp)
                                        createDownPointer(xPosition+60, y_pointer, "P");
                                temp = ptArray[temp];
                                nodeNum++;
                        }
                }
		xPosition = calcDistance(nodeNum);
		if (temp == -2 && nodeNum > 0){
			createNodeEmptyTop(xPosition, y_node);
		}
		else if (temp == -1 && nodeNum > 0){
        	        createNullBox(xPosition, y_nullBox);
		}
		graphicsBottomNodes();
	});
}

//	Graphics for nodes not connected to Front or 
//	before Front pointer
function graphicsBottomNodes() {

        $.getScript('objectCreation.js', function () {
		var i;
		var j;
		var xPosition;
		var nodeNum;

                nodeNum = 0;
                var osFlag = false;
                for (i=0; i<MAXNODES; i++){
                        for (j=0; j<onScreen.length; j++){
                                if (i == onScreen[j])
                                        osFlag = true;
                        }
                        if (osFlag == false && valArray[i] != -1){
                                xPosition = calcDistance(nodeNum);
				if (ptArray[i] == -1)
                                        createNodeBottom(xPosition, y_nodeBot, valArray[i], "X");
				else if (ptArray[i] == -2)
					createNodeBottom(xPosition, y_nodeBot, valArray[i], "?");
				else
	                                createNodeBottom(xPosition, y_nodeBot, valArray[i], valArray[ptArray[i]]);
                                if (R == i)
                                        createDownPointer(xPosition+85, y_pointerBot, "R");
                                if (S == i)
                                        createDownPointer(xPosition+35, y_pointerBot, "T");
                                if (pointP == i)
                                        createDownPointer(xPosition+60, y_pointerBot, "P");
                                nodeNum++;
                        }
                        osFlag = false;
                }
                onScreen.length = 0;
		graphicsNullPointers();
	});
}

//	Graphics for Null or junk Pointers (if there is any)
function graphicsNullPointers() {
	$.getScript('objectCreation.js', function () {
		var xPosition = 30;
		if (F == -1){
			createSidePointer(xPosition, y_sidePointer, "F", "X");
			xPosition += 80;
		}
		if (F == -2){
                        createSidePointer(xPosition, y_sidePointer, "F", "?");
                        xPosition += 80;

		}
		if (S == -1){
                        createSidePointer(xPosition, y_sidePointer, "T", "X");
                        xPosition += 80;
		}
                if (S == -2){
                        createSidePointer(xPosition, y_sidePointer, "T", "?");
                        xPosition += 80;

                }
                if (pointP == -1){
                        createSidePointer(xPosition, y_sidePointer, "P", "X");
                        xPosition += 80;
                }
                if (pointP == -2){
                        createSidePointer(xPosition, y_sidePointer, "P", "?");
                        xPosition += 80;

                }
                if (R == -1){
                        createSidePointer(xPosition, y_sidePointer, "R", "X");
                        xPosition += 80;
                }
                if (R == -2){
                        createSidePointer(xPosition, y_sidePointer, "R", "?");
                        xPosition += 80;
		
                }

	});
}

//	Create graphics with current info
function graphics()
{
	graphicsTopNodes();
//	graphicsBottomNodes();
//	graphicsNullPointers();
}

//-------------------------------------------------------------------

/*
	This function is used to see how the information being
	passed back from cgi.

	Usage only during development!
*/
function printData(data)
{
	$('#response').append('left/right text: ' +
		data.left + ' ___ ' + data.right);
	$('#response').append('<br />');
	$('#response').append('left/right Value: ' +
		data.leftNum + ' ___ ' + data.rightNum);
	$('#response').append('<br />');
	$('#response').append('Last: ' + data.lc + " ___ " +
		data.lsc + " ___ " + data.len);
	$('#response').append('<br />');
	$('#response').append('Curr Array: ' + data.pa
		+ ' ___ ' + data.va);
	$('#response').append('<br />');
	$('#response').append('Old Array: ' + data.opa +
		' ___ ' + data.ova);
	$('#response').append('<br />');
	$('#response').append('Curr Pointers: ' + data.f + ' ___ ' +
		data.r + ' ___ ' + data.s + ' ___ ' + data.pointP);
	$('#response').append('<br />');
	$('#response').append('Old Pointers: ' + data.of + ' ___ ' +
		data.or + ' ___ ' + data.os + ' ___ ' + data.opointP);
	$('#response').append('<br />');
        $('#response').append('Flags: ' + data.sf + ' ___ ' + data.ilf +
		' ___ ' + data.ff + ' ___ ' + data. uef);
	$('#response').append('<br />');
	$('#response').append('Done');

}

//	Check for errors and alert if there is one
//	Otherwise, update info
function checkData(data)
{
	if (data.sf == 'true')
		alert('Error: Segmentation Fault');
	else if (data.ilf == 'true')
		alert('Error: Infinite Loop');
	else if (data.ff == 'true')
		alert('Error: Max Nodes');
	else if (data.uef == 'true')
		alert('Error: Cannot Undo');
	else if (data.cf == 'true')
		alert('Error: Circular linked list');
	else
		updateAll(data);
}

/*
	This function will pass new information to cgi.
	The cgi will determine what to do with the info.
	Once the information is passed back, it will 
	update the information and give the appropriate 
	graphics.

	If the change would cause an error, alert will 
	tell what the error is and not go through with
	the change.
*/
function passCGI(leftText, rightText, leftVal, rightVal, valChoice)
{
                $('#response').html('<br />');

	if (valChoice == undefined)
		valChoice = 0;
	if (leftText == undefined)
		leftText = '-';

                var ptArray1 = arrayToString(ptArray);
                var valArray1 = arrayToString(valArray);
                var oPtArray1 = arrayToString(oPtArray);
                var oValArray1 = arrayToString(oValArray);

                $.get("/cgi-bin/vu033/cgiLlist.cgi",
                        { leftChoice : leftText,
                          rightChoice : rightText,
                          lChoice : leftVal,
                          rChoice : rightVal,
                          elementNum : valChoice,
                          lastCommand : lCommand, lastSubChoice : lSubChoice,
                          lastElementNum : lElementNum, pointerArray : ptArray1,
                          valueArray : valArray1, oldPointerArray : oPtArray1,
                          front : F, rear : R, second : S, P : pointP,
                          oldFront : oF, oldRear : oR, oldSecond : oS,
                          oldP : oldPointP, oldValueArray : oValArray1,
                          segFlag : sFlag, infLoopFlag : infFlag, fullFlag : fFlag,
                          undoErrFlag : undoFlag
                        },
                        function(data) {
                                if (data) {
                                        //printData(data);
                                        checkData(data);

                                        paper.clear();
					graphics();
                                }
                                else
                                        $('#response').append("Oops");
                                if (lCommand == 13)
                                        lCommand = 1;

                });

}

//	Resets all graphics
function resetGraphics()
{

	paper.clear();
        $.getScript('objectCreation.js', function () {

                createDownPointer(60, 70, "F");
                createDownPointer(85, 70, "T");
                createDownPointer(110, 70, "P");
                createDownPointer(435, 70, "R");
                createNodeTop(50, 110, valArray[0]);
                createNodeTop(200, 110, valArray[1]);
                createNodeTop(350, 110, valArray[2]);
                createNullBox(500, y_nullBox);

        });
}

//	Resets all variable 
function reset ()
{

	lCommand = 13;
	lSubChoice = -1;
	lElementNum = -1;

	ptArray = [1, 2, -1, -1, -1];
	valArray = [17, 14, 8, -1, -1];

	onScreen = [];

	oPtArray = [-1, -1, -1, -1, -1];
	oValArray = [-1, -1, -1, -1, -1];

	F = 0;
	R = 2;
	S = 0;
	pointP = 0;

	oF = -1;
	oS = -1;
	oR = -1;
	oldPointP = -1;

	sFlag = false;
	infFlag = false;
	fFlag = false;
	undoFlag = false;

	resetGraphics();

}

/*
	This function create the appropriate response
	for each button
*/
$(document).ready(function() {

	$('#setPointerButton').click( function () {
		passCGI( $('#setPointer .lval option:selected').text(),
			 $('#setPointer .rval option:selected').text(),
                         $('#setPointer .lval option:selected').val(),
                         $('#setPointer .rval option:selected').val());
	});

	$('#setElemButton').click( function () {
		var valChoice = document.getElementById('elemNum').value;
		if (valChoice > 0 && valChoice < 100){
			passCGI( $('#setElem .lval option:selected').text(),
				 'Enter Value',
				 $('#setElem .lval option:selected').val(),
				 '-1',
				 valChoice);
		}
	});

	$('#createNodeButton').click( function () {
		passCGI( $('#createNode .lval option:selected').text(),
                         'newNode',
                         $('#createNode .lval option:selected').val(),
                         '1');
	});

	$('#deleteNodeButton').click( function () {
                passCGI( 'delete',
                         $('#deleteNode .rval option:selected').text(),
                         '12',
                         $('#deleteNode .rval option:selected').val());
	});

	$('#undoButton').click( function () {
		passCGI( $('#misc #undoButton').text(), 'none',
			 $('#misc #undoButton').val(),'-1');
	});

	$('#resetButton').click( function () {
		reset();
	});
});


















