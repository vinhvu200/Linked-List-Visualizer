/*
	-This file contains all the graphics to be created
*/

function test () {

/*
	var circle = paper.circle(0, 0, 10);
        circle.attr({'stroke-width': 2});
        var arrow = paper.path("M 10 0 l 30 0");
        arrow.attr({'arrow-end': 'classic-wide-long', 'stroke-width': 2.5});
        var text = paper.text(0, 0, label);
        text.attr({'font-size': 15, 'font-weight': 'bold'});
        var x = paper.text(50, 0, "?");
        x.attr({'font-size': 18, 'font-weight': 'bold'});
        var sidePointer = paper.set(circle, arrow, text, x);
        sidePointer.transform("T" + xpos + " ," + ypos);
*/	
	createSidePointer(200, 200, "F", "?");
}

function createNodeTop(xpos, ypos, element)
{
	if (element == 0)
		element = '';
	
        var text = paper.text(50, 30, element);
        text.attr({'font-size': 25, 'font-weight': 'bold'});
        var arrow = paper.path("M 115 30 l 30 0");
        arrow.attr({'arrow-end': 'classic-wide-long', 'stroke-width': 2.5});
        var outsideBox = paper.path("M 0 0 l 100 0 l 0 15 M 0 0 l 0 60 l 100 0 l 0 -15");
        outsideBox.attr({'stroke-width': 3});
        var circle = paper.circle(100, 30, 15);
        circle.attr({'stroke-width': 3});
        var Node = paper.set(text, arrow, outsideBox, circle);
        Node.transform("T" + xpos + " ," + ypos);
        return Node;
}

function createLastNodeTop(xpos, ypos, element)
{
        var outsideBox = paper.path("M 0 0 l 100 0 l 0 15 M 0 0 l 0 60 l 100 0 l 0 -15");
        outsideBox.attr({'stroke-width': 3});
        var circle = paper.circle(100, 30, 15);
        circle.attr({'stroke-width': 3});
        var text1 = paper.text(50, 30, element);
        text1.attr({'font-size': 25, 'font-weight': 'bold'});
        var text2 = paper.text(100, 30, "X");
        text2.attr({'font-size': 20, 'font-weight': 'bold'});
        var Node = paper.set(outsideBox, circle, text1, text2);
        Node.transform("T" + xpos + " ," + ypos);
        return Node;

}

function createNodeEmptyTop(xpos, ypos)
{
        var rect = paper.rect(0, 0, 100, 60);
        rect.attr({'stroke-width': 3, 'stroke': 'gray' });
        var text = paper.text(50, 30, "?");
        text.attr({'font-size': 25, 'font-weight': 'bold', 'fill': 'gray'});
        var Node = paper.set(rect, text);
        Node.transform("T" + xpos + " ," + ypos);

        return Node;
}

function createNodeBottom(xpos, ypos, element, label)
{
	if (label == -1)
		label = 'X';
	if (label == undefined || label == -2)
		label = '?';

	if (element == 0)
		element = '';

        var outsideBox = paper.path("M 0 0 l 100 0 l 0 15 M 0 0 l 0 60 l 100 0 l 0 -15");
        outsideBox.attr({'stroke-width': 3, 'stroke': 'gray' });
        var circle = paper.circle(100, 30, 15);
        circle.attr({'stroke-width': 3, 'stroke': 'gray'});
        var text1 = paper.text(50, 30, element);
        text1.attr({'font-size': 25, 'font-weight': 'bold', 'fill': 'gray'});
	var text2 = paper.text(100, 30, label);
	text2.attr({'font-size': 15, 'font-weight': 'bold', 'fill': 'gray'});
        var Node = paper.set(outsideBox, circle, text1, text2);
        Node.transform("T" + xpos + " ," + ypos);
        return Node;
}

function createNullBox (xpos, ypos) {

	if (xpos == undefined || ypos == undefined){
		xpos = 35;
		ypos = 35;
	}

        var nullBox = paper.path("M 0 0 l 20 0 l 0 20 l -20 0 \
                                l 0 -20 l 20 20 m 0 -20 l -20 20");
	nullBox.attr({'stroke-width': 2});
	nullBox.transform("T" + xpos + " ," + ypos);

	return nullBox;
}

function createDownPointer (xpos, ypos, label) {

	if (xpos == undefined || ypos == undefined){
                xpos = 35;
                ypos = 35;
        }
	if (label == undefined)
		label = '';

	var circle = paper.circle(0, 0, 10);
        circle.attr({'stroke-width': 2});
        var arrow = paper.path("M 0,10 l 0,25");
        arrow.attr({'arrow-end': 'classic-wide-long', 'stroke-width': 2});
        var text = paper.text(0, 0, label);
        text.attr({'font-size': 15, 'font-weight': 'bold'});
        var downPointer = paper.set(circle, arrow, text);
        downPointer.transform("T" + xpos + " ," + ypos);

        return downPointer;
}

function createSidePointer (xpos, ypos, label, dest) {
        var circle = paper.circle(0, 0, 10);
        circle.attr({'stroke-width': 2});
        var arrow = paper.path("M 10 0 l 30 0");
        arrow.attr({'arrow-end': 'classic-wide-long', 'stroke-width': 2.5});
        var text = paper.text(0, 0, label);
        text.attr({'font-size': 15, 'font-weight': 'bold'});
        var x = paper.text(50, 0, dest);
        x.attr({'font-size': 18, 'font-weight': 'bold'});
        var sidePointer = paper.set(circle, arrow, text, x);
	sidePointer.transform("T" + xpos + " ," + ypos);

	return sidePointer;

}

function createUpPointer (xpos, ypos, label) {

	if (xpos == undefined || ypos == undefined){
		xpos = 35;
		ypos = 35;
	}
	if (label == undefined)
		label = '';

	var circle = paper.circle(0, 0, 12.5);
        circle.attr({'fill': 'gray', 'stroke': 'gray'});
        var arrow = paper.path("M 0,-12.5 l 0,-25");
        arrow.attr({'arrow-end': 'classic-wide-long', 'stroke-width': 2,
                        'stroke': 'gray'});
        var text = paper.text(0, 0, label);
        text.attr({'font-size': 15, 'font-weight': 'bold', 'fill': 'white'});

        var upPointer = paper.set(circle, arrow, text);
        upPointer.transform("T" + xpos + " ," + ypos);

        return upPointer;


}

