# Linked List Visualizer
This project was done with Professor Rika Yoshii for my Summer Scholar Project, sponsored by ViaSat. This web application was created to aid students in learning the Linked List data structure through visualization. 

Check it out here: http://cis444.cs.csusm.edu/ryoshii/vu/
One of the button is off centered on Mac so I'm sorry :( 

# Visualization
![Image 1](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/1.png "Image 1")

- Nodes are represented as a rectangle with a circle attached to it
- Number inside the rectangle is its element
- Number inside the circle is the node it is pointing to
- The circle represents the node's pointer
- 'X' represents NULL
- '?' represents junk
- F (Front), P, T, R (Rear) represent pointers to move around

# Top Section
![Image 2](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/2.png "Image 2")
![Image 3](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/3.png "Image 3")

- Top section represents all the nodes connected together from Front pointer onward
- It continues until it reaches NULL or junk
- It is good practice to keep Rear pointer on the last node here

# Bottom Section
![Image 4](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/4.png "Image 4")

- Bottom section represents all nodes not connected after the Front pointer
- These nodes are lighter to show they are not part of the main linked list
- First node: Node with element 14 pointing to junk
- Second node: Node with element 30 pointing to NULL
- Third node: Node with element 40 pointing to Node with element 20

# Dangling Pointers
![Image 5](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/5.png "Image 5")

- Dangling pointers will be placed on the top left
- These pointers do not point to any specific nodes

# Actions
![Image 6](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/6.png "Image 6")

- All possible actions are divided into three sections: Set Pointer, Set Element, Delete Node
- These make up actual code normally written to handle a linked list

# Set Pointer
![Image 7](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/7.png "Image 7")

This section allows you to...
- Create new Nodes
- Set a pointer to NULL
- Freely move pointers around

# Set Element
![Image 8](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/8.png "Image 8")

This section allows you to...
- set the value of a node to a number between 1 and 99 inclusive
- No two nodes may have the same element for the purpose of simplicity of this tool

# Delete Node
![Image 9](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/9.png "Image 9")

This section allows you to...
- Delete a node referenced by a pointer
- Remember that when a node is deleted, nodes pointing to the deleted node will now point to junk

# Segmentation Faults
![Image 3](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/3.png "Image 3")

- Segmentation faults occur when you reference junk
- Example: 'T = T -> next' will cause segmentation fault

![Image 10](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/10.png "Image 10")

- A message like this will appear to indicate so

# Memory Leak
![Image 11](https://github.com/vinhvu200/Linked-List-Visualizer/raw/master/DemoImages/11.png "Image 11")

- A node that can no longer be referenced causes a memory leak
- In this case, the node with element 33 cannot be reached anymore; therefore, causing a memory leak


