# **Powder Of Life**

## Manual and Overview of the Framework and Methodologies

# **Overview**

Powder Of Life (POL) is a framework for building things. You can create musical instruments, autonomous robots, oversized interfaces, interactive sculptures, or whatever other weird thing your heart desires. POL allows you to connect components together easily and get robust, predictable behavior.

POL is also a philosophy, it is a way of solving problems and building things, and it is a collection of artifacts for learning.

## **Usage**

Powder Of Life is designed to work out of the box, but it does assume that you are familiar with each environment it operates in. This is why POL is geared toward an educational context. It is more effective when there is a mentor to help facilitate the explorations. Though, you are welcome to dive in\!

In terms of software, you will need to download the libraries [link?] and install them into each specific environment. These installed libraries come with examples specific to each environment. You can learn how to use POL by running the examples. Each example is built around a kind of meaningful interaction. If you are ready to dig in, see the API / reference [link?] for specific components and their available methods.

In terms of hardware, you will need to print or cut the provided designs and purchase the appropriate motors, electronics, fasteners, and other parts. For example, there are many 3D printable parts in POL that are designed to work with metric nuts and bolts which will need to be added to complete the interface. There are also parts are designed around commercially available motors (such as a standard hobby servo motor). In most cases, the designs provided in POL fit the parts that you can purchase “off the shelf”, but some adjustment (custom development) may be required depending on what’s available or what you already own.

A good starting point would be to run examples in each environment. For example, build the “LED Candle” example in the Arduino library. It features a very simple network and electrical circuit and requires downloading code to the Arduino board. Once you’ve mastered that, maybe move into Unity and run the “Lerp Node and Transform Driver with trails” example. It has a simple network and an animation that helps make the function of those neurons clear. And once that feels comfortable, try combining both environments at the same time with the Serial Echo examples. You’ll have to load the Serial Echo Arduino example onto your board, close the IDE (or else you’ll get a port conflict), then run the Serial Echo example in Unity to see it bounce a message off the Arduino board and give you a visual feedback in Unity once the message makes a round trip.

Powder Of Life supports a la cart (partial) usage, so you can implement features ad hoc. You can write support code around it. When you get to this point, [explore the API](API/README.md) for more information. Also see [Integration](\#Integration) below.

## **Origins**

### **We're not in Kansas anymore**

The fantastic name, Powder Of Life, comes from [L. Frank Baum's Oz series](https://en.wikipedia.org/wiki/The\_Marvelous\_Land\_of\_Oz). If you sprinkle the powder on something, and say the magic words, the inanimate object will come to life. For example, the [Jack Pumpkinhead](https://en.wikipedia.org/wiki/Jack\_Pumpkinhead) and the [Sawhorse](https://en.wikipedia.org/wiki/List\_of\_Oz\_characters\_(created\_by\_Baum)\#Sawhorse).

### **Why I built a framework**

I developed POL in response to both my own research and the needs of my students. It began as a collection of components that were developed from recurring problems in teaching new media art classes. Students in these classes are struggling through multiple specializations to achieve their goal (electrical, mechanical, and software engineering). I have found that my best contribution in that process is a simple, well-written script, properly compartmentalized to do a task well, or a cleanly designed 3D model, with parts properly named and separated for easy modification. The artifacts that came out of this process eventually became the foundation of the Powder Of Life framework.

To see examples of how you might use POL, start by looking at my [personal website](https://andrewfrueh.com). It has links to all the places I post currently on social media, and you can see how I am currently using POL.

### **Goals**

POL is as much a philosophy as it is anything. The reason for the various assumptions and rules stem from the philosophical roots.

In outlining the framework, I took inspiration from thinkers like Valentino Braitenberg, Seymore Papert, Vannevar Bush, and Doug Englebart. I wanted POL to be a system that could create a wide range of interesting behavior from components that were easy to rearrange and could allow you to learn as you go. And as a teacher, I wanted it to serve the kinds of students I worked with: an art student should be able to use it to build a crazy interactive installation they dreamed up; an engineering student should be able to use it to study a foundational concept like quadrature encoding for that upcoming exam.

The primary goal for POL is for it to be a collection of idealized artifacts that serve both as building blocks and as educational tools. This collection of artifacts should include examples (meta-artifacts) that serve as tutorials for using POL, as starting points for real projects, and as points of topic-specific educational exploration.

### **Physical Computing**

Building interfaces and interactive artwork can help you become a better engineer. You learn a lot from the reality of trying to build things that hold up to the real world, and creating physical interfaces makes your digital system more dynamic and interesting to interact with.

In porting Powder Of Life from Unity (in C\#) to Arduino (in C++), I was forced to be more rigorous in abstracting each component. The act of building interfaces for these digital creations made the components more idealized which also made them more portable. This made the whole framework stronger. It also opens the door for POL to move into even more environments. Like the Borg on Star Trek, the more POL comes in contact with, the stronger it grows – “you will be assimilated.”

And as for human-computer-interaction (HCI), the more we can explore different ways of interfacing with technology, the more we can open the bottleneck between us and the technology and explore the true power of our human potential (see Engelbart below).

At the time of writing this, the trend is (and has been for decades now) toward stupefying the our interfaces with technology. While most musical instruments require at least a few fingers (and possibly multiple limbs), our most common interactions with the infinite universe of digital technology is performed on our phones with just a single finger (or maybe two thumbs).

Powder Of Life invites the creating of new and novel ways to interact with technology (or for technology to interact with itself). Physical computing is about designing interfaces that leverage the reality of living in physical bodies. POL allows you to glue things together in unexpected ways yet end up with a system that performs reliably.

One big hurdle to building physical computing systems is the difficulty of communication across different environments. Each environment has its own standards, and often interoperability is poor even within a single environment. This is why POL has a strong focus on standardizing the flow of data through the network.

You start with a big lever, or a sensor that detects movement. The input enters the network there, and moves through some low-level electronic circuits (maybe a PCB breakout board), then goes through a micro-controller (like an Arduino), then goes to a computer (maybe a laptop running Unity) to be further processed, and then goes back out to a micro-controller to perform some action, like moving a servo motor. As the data moves through this system, you will face constant hurdles of translation and normalization.

From this perspective, Powder Of Life is really just an imposed set of standards with a bunch of translations or mappings for specific systems. This definition helps clarify why POL has hardware components. Components do not need to be involved in data processing (as with neurons). What is important is standardizing the interactions between systems. POL fills in gaps in interoperability.

The framework of Powder Of Life is there to create stability and deliver behavior so that you can focus on the hard work of exploring different configurations and morphologies and see what new ways we can interact with these systems.

## **Design Decisions**

### **Biological Analogies**

The organization of all this work began as a project called “sensor driver network”. One of the main inspirations at that point was Braitenburg’s Vehicles (see below) and very simple life forms like a hydra or jellyfish (phylum Cnidaria). I was interested in how responsive behavior could emerge from simple analog systems.

I drew upon those biological analogies for the structure of POL. As with a biological nervous system, all active components in a POL network are “neurons”. The type of neuron varies depending on it’s role in the network. POL is not like a brain, it’s more like a nervous system.

At the time of writing this, there is much hot talk of “neural networks” – mostly related to ML (a.k.a. “AI”). It should be noted that this is all related to neurons found in the brain, primarily in the cerebral cortex specifically. It should also be noted that current artificial neural networks (ML) are not at all like the networks in the cerebral cortex in terms of topology.

Putting all that aside, neurons are neurons. While brains may be made of neurons, having neurons doesn’t mean you have a brain. All animals have neurons. Hydra have neurons – albeit their network is so simplistic we use the special term “nerve net”. In all animals, there are specialized neurons that are wired directly to tissues or special receptors – so called “sensory neurons.” Then there are neurons wired directly to muscle tissue – so called “motor neurons.”

It is from these concepts that POL gets its Sensor and Driver classes, and it is from this perspective that Powder Of Life uses the term “neuron”. The whole point of POL is to assemble these simple networks so you can get robust analog behavior and learn what works. You use POL to thread a nervous system through your project. Data flows in from sensors, possibly flows through some nodes, and finally comes out the other end of drivers.

### **Analog Normalized Data**

The choice for a normalized, analog data-flow came from constantly having to map values between systems. I could see that specific components designed around each type of system could establish the mapping, and then normalized data could just flow through the system with predicable results.

### **Node-and-wire**

The choice of a network of objects connected end-to-end comes from the reality of passing data through a process and the need to make flow explicit. In node-and-wire environments (found in Blender, Unreal, Max/MSP, Grasshopper/Rhino, etc.) there is an imposed constraint of how you are able to wire the nodes together. In laying out the nodes linearly, you can see how the data will flow from one end to the other – branching and bottlenecking along the way. You will come to realize the splitting values is easy as you can just connect an output to multiple other nodes, but merging data is hard since you need to decide how to merge or what merging means. This set of constraints is adopted by POL with it’s neurons connected end-to-end, from sensor to driver.

The downside of node-and-wire interfaces is that they are not strong programming environments. No offense intended, but there is a reason that the really tough things are done with pure text coding environments. Text is such a dense and powerful medium. Text allows you to copy, move, and translate code with ease – even across different environments. It allows you to perform complex search and replace operations (supported by tools like regex). And it allows you to leverage chatbots (LLMs) to help you write code snippets.

Powder Of Life provides the benefits of a node-wire interface (without the hassle of drawing shapes to write code), and all the benefits of writing code in pure text.

### **Metric Units**

The choice of using metric units in physical designs is to make them conceptually similar to the normalized data flowing through the system. For many physical connectors, the holes are spaced on a metric grid with 1cm (or another power of 10, i.e. 10cm, 1m, 10m, etc.) spacing. This “normalizes” the physical space which makes it easier to rearrange physical components to achieve desired behavior. Additionally, when you work with these normalized physical components in the physical environment (with their possible electromechanical empowerment) you are more likely to discover unexpected relationships and make new discoveries – which is kind of the point of Powder Of Life.

## **Influences**

### **Papert’s Turtle**

Like his mentor Jean Piaget before him, Symore Papert believed that children learn by building (“constructing”) their knowledge as they interact with the world. He also believed that play had a central role in this learning exploration. He designed LOGO and the character of the “Turtle” to create a sandbox where a student can play by combining simple rules as a way to learn computer control and system dynamics.

In this same vein, Powder Of Life is designed as a sandbox of simple components that can be combined  playfully while still producing meaningful behavior. Furthermore, the components in POL are designed for further inspection, and possible code-theft for future projects.

### **Braitenberg’s Vehicles**

There is a wonderful little book from 1984 by Valentino Braitenberg called Vehicles: Experiments in Synthetic Psychology. In this book, Braitenberg outlines some simple robots that exhibit complex behavior.

The key relationship (especially in the first few vehicles) is between a sensor and a motor. A robot with just two sensors and two wheels can either pursue or avoid stimulus depending on which way you connect the wires.

This relationship was an inspiration for an early prototype sensor-driver network I built in Unity. Being an artist, I soon wanted to connect these game-engine experiments to the real world. This caused me to extend the framework into the Arduino environment.

### **Bush’s Analog Computing**

In the midst of WWII, Vannevar Bush, the scientific advisor to Franklin D. Roosevelt, did not support the building of the world’s first digital computer. He estimated they wouldn’t be done before the end of the war – which he turned out to be right about.

Before digital computers, how did they do complex calculations? They used analog computers. In place of writing code that calculates equations as we do today, they crafted mechanical linkages and interlocked gears to create an output that provided the correct answer. This may sound crazy now, but at the time, it’s what they had. Today, we have ultra-fast digital computers that can run simulations controlled with computer code. The computers are so fast, that we can now simulate analog systems through digital hardware.

Powder Of Life is just such a simulated analog system. The Neurons in POL assume a floating-point value between zero and one. Most of the behavior in POL is a result of analog values bouncing off each other. It requires a balancing of components that I think Vannevar would approve of.

### **Engelbart’s Bottleneck**

Having read Vannevar Bush’s *As We May Think* some years before, Doug Engelbart wrote about the interface between humans and computers in *Augmenting Human Intellect* (1962). He was concerned that between the infinite world within our mind and the infinite world within the digital computer, there was a potential bottleneck through the interface. Engelbart went on to design the computer mouse and GUI which he and his team presented in the “Mother of All Demos” in 1968\. These great ideas, laying around waiting for a purpose, were picked up by a young Steve Jobs to be used as the foundation for the Macintosh operating system.

And while Steve was good at making things sleek and simple, Doug would regularly point out that the goal of making the interface easier was dumbing down our ability to leverage these powerful new environments. Steve jobs loved to refer to the Mac as the “bicycle of the mind”. Doug Engelbart would often say in response that the way the interfaces were going, it was more like an adult “riding a tricycle” and that instead he wanted us to be riding ten-speeds.

Powder Of Life has connections to both points of view, depending on the context (sometimes simple is good). But in terms of fostering human potential, POL is solidly in Engelbart’s camp. It is far more important to open the bottleneck between the human and the machine, even if that requires a come complex interface with a steeper learning curve. Sometimes great things take some work. There’s a big difference between the violin Doug Engelbart hopes for us to have and the kazoo that Steve Jobs wants us to buy.

### **Construction Set Toys**

At the turn of the twentieth-century, an English clerk named Frank Hornby designed a new way to explore mechanical engineering through a set of modular parts that children could explore on their own. His creation would eventually be known as Meccano, and it would become so popular that Frank had to set up his own manufacturing facility to meet demand. As the world marched into WWI, the competing Erector brand would pop up in the US, only to be purchased by Meccano some decades later. As WWII came to a close, a woodworking company in Denmark began producing the item that would eventually come to dominate the modern construction-toy market worldwide – the plastic Lego brick.

# **Development Rules**

## **Purpose**

The development rules ensure new artifacts within the POL framework are appropriately idealized. This means they should be abstract, compartmentalized, and designed to be reusable and easily understood. The primary goal is to make POL components that are "idealized artifacts" that operate as both building blocks and educational tools.

## **Development Workflow**

* **Define Abstractly:** Begin by defining the problem / solution space abstractly. What is the generalized model of the kind of problem you are dealing with? Keep in mind that this space may be made up of multiple sub-spaces – in other words, you may be dealing with a complex problem / solution that is actually made up of smaller problems / solutions. Define this landscape first.

* **Compartmentalize Scope:** Once you have abstracted / defined the problem / solution space (or spaces), you can outline the scope (or scopes) that will need to be focused on. Define each scope as clearly as possible.

* **Focus and Develop:** When the scope (or scopes) have been defined, you can move on to actual development. Keep development focused on the defined scope. Be willing to “dive down the rabbit hole” and get close to the problem. Be willing to get your hands dirty. Note that if development becomes overly complex, there may be an issue with the scope or abstraction layers. Be willing to step back and reassess the previous layers if it seems necessary.

## **Naming Conventions**

Since POL operates in multiple environments, when new features are being developed, it is necessary to consider potential conflicts that could arise due to arbitrary choices.

For example, in the software environments, there are many keywords (or other reserved symbols) that that have set behaviors. Each potential conflict will need to be assessed and a different design decision may be required.

In the Unity environment, the method Update() is called automatically on all components by the Monobehavior framework. The use of Update() by POL is acceptable as we can piggyback off this functionality – it’s what we want anyway. However if “update” is a method or keyword in an environment that POL moves into and the behavior is not what we want, we would need to make a different choice (pick a different word for that method).

Compare this to the word “while” which is a keyword for creating loops in almost every programming language. Using this word in code would never be advised (except for creating actual while loops) as it is integral to the programming language and should be avoided.

## **Guiding Principles for Finished Components**

* **Abstraction:** Every solution should be extracted out to it’s most idealized form. An abstract representation can more easily be cast into different contexts and environments making the solution more portable and generally applicable to a wider range of problems.    
* **Compartmentalization:** Every solution should be focused on the tightest possible scope. If a solution performs multiple tasks, it should be split into separate solutions for each task. This allows for greater reusability and flexibility as individual solutions can be used independently or recombined as needed.  
* **Portability:** Components should be designed to function in multiple environments with minimal modification. Each environment has it’s own requirements, but good abstraction and compartmentalization support greater portability.  
* **Exemplar Components:** Every component should serve as a clear example of how to solve a specific problem within the POL framework. Think of these as meta-artifacts that double as tutorials, starting points for projects, and topic-specific educational explorations.  
* **Thorough Documentation:** Comment your code extensively to explain the purpose and functionality of each part of your components. Use clear and descriptive language to make your code easy to understand.  
* **Descriptive Naming Conventions:** Use complete and meaningful names for variables, functions, and classes. This makes the code more readable and self-documenting. Avoid programming jargon and abbreviations that might confuse users unfamiliar with specific coding conventions.

## **Network Expectations**

* **Normalized Data:** All data should be normalized to a 0-1 range when possible. This creates better interoperability between components (especially across different environments). And uniform values make it easier to asses the state of the system at any particular point.

* **Read-Forward Data Flow:** Ensure all data flows in a consistent direction within your components. In POL, data moves through a network in a read-forward manner, with neurons receiving input from a preceding neuron. Each neuron reads the output (state) of the neuron before it. For example, a driver neuron would read the output of a sensor neuron.

## **Mechanical Expectations**

* **Normalized Dimensions:** All physical dimensions (spacing of holes, widths of parts, etc.) should be sized to metric units and should align to a grid based on powers of ten when possible. For example, if a motor-mount has holes along the edge for attaching it to a frame, these holes should be spaced in 1cm (or 10cm, or 1m) increments – this way it can be attached to any other part that features the same hole-spacing. This makes physical parts more modular and makes POL into a “construction set” similar to Meccano, Erector, Lego, etc.

* **Standardized Connections:** When designing flanges and other parts where physical connections will take place, optimize for the widest range of possible options. This will often require iteration as you will need to fabricate parts and then play with them to see how they go together. Do this exploratory work up front (in the fuzzy front end) as changes will be more difficult later as designs stabilize. Try to find a set of sizes and angles that can be combined in a lot of ways while still serving the function of making simple connections when needed. Consider the spacing of mount holes (see normalized dimensions above).

* **Parameterized Designs:** Physical designs can also be abstracted and compartmentalized through parametric modeling. It is often necessary to draw up parts by hand when you are iterating a design and it is changing rapidly. You want to reduce constraints so you can modify aggressively. But as the design stabilizes, you should go back and recreate it as a parametric CAD type design whenever possible. Lock in required elements within the component, and expose the parameters that will allow a user to create new variations without needed to make changes to the component itself.

## **Integration**

* **Light Touch:** Each component should be designed around existing products, features, standards for “light touch” integration. Since the goal of POL is to increase interoperability between disparate systems, it is often necessary to develop new interfaces or wrappers around existing systems, but this should be done in a non-invasive way, leaving as much of the system unmodified as possible.

* **A La Cart:** Components should be usable as-needed. This means they should not depend upon other active components unless required (e.g. the trio of Serial components). The goal is to be able to write code as you need to around POL, to use components “a la cart.” This may require altered usage of components – for example, in the Arduino environment, to use a component manually, it should not be registered with the Engine (as normal), but will instead need to be updated manually (in your code).

# **Types of Systems**

Powder Of Life is designed around many types of systems across multiple environments. Often POL components are designed as solutions to interface problems for existing components / hardware. As such, here is a glossary of different systems that POL interacts with (has solutions for).

## **Encoders**

Encoders help mechanical systems know where they are (e.g. printers), there can generally be put into two categories, relative (common and inexpensive) and absolute (less common, more expensive). The EncoderSensor handles the relative (quadrature, bar pattern type), while the AnalogSensor is fine for the absolute type (my IR sensor plus gradient type).

### **Relative**

The most common type. Can be found in any inkjet or 3D printer. Cheap to implement and very accurate tracking if speeds are kept below a certain threshold.

The trick to a relative encoder is a pair of sensors that travel along an encoder strip. The sensors need to have a specific spacing or “pitch”, and the encoder strip needs to have a regular spacing that is set with consideration to the pitch of the sensors. In a typical setup, this is a pair of infrared reflectance sensors and a bar pattern (alternating black and white tiles) printed or etched onto the surface of the encoder strip.

There are two ways to set this up, in serial with one bar pattern and the two sensors traveling in tandem, or in parallel with two bar patterns and the two sensors traveling side-by-side (with the necessary offset between the two bar pattern tracks).

It should also be noted that while this is typically optical (IR sensors), encoding can be done with any pair of sensors that can be setup to travel over a surface with a regular pattern so long as you can set the pitch of the sensors to match the pattern being used as the encoder.

#### ***Quadrature Encoding***

Parsing the amount traveled and in which direction is done with Quadrature. There are four states that are possible with two sensors.

| 0 | 0 |
| :---: | :---: |
| 1 | 0 |
| 1 | 1 |
| 0 | 1 |

Use an EncoderSensor to handle quadrature encoded input. The two pins will cycle through the states above, and from this, the sensor can determine both how many steps and in which direction the encoder is moving.

### **Absolute**

Can be tricky to pull off. Many currently available designs include multiple bar patterns overlaid across multiple tracks.

The current solution in POL is to use a gray-scale gradient and an infrared reflectance sensor. However, more research needed to correct the curve implicit in printing such a pattern (currently I get non-linear behavior).

In the case of this gradient with IR sensor, use an AnalogSensor to handle the input (i.e. “encoding”).

For even more precise action, it should be possible (though I’ve not implemented it) to have both a relative bar pattern track and a gray-scale gradient track side by side with sufficient IR sensors for both.

## **Motors**

Motors move things. They are the muscles of your project. They are a lot of fun to work with, but they have intense power requirements that need to be respected – if not, you will get weird behavior that will be difficult for a novice to diagnose.

Typically, you use a dedicated power supply that is managed through a motor-driver board (a separate PCB). So the interface on the POL side is mainly about aligning with the inputs on that motor-driver board.

### **DC (standard and geared)**

A typical interface for DC motor-driver boards is one pin to control direction and another pin to control speed. The direction pin takes a digital signal – the true/false simply flips the polarity. The speed pin takes a PWM signal (simulated analog).

A DC motor has two wires. These wires are connected to the outputs on the motor-driver board. The board will control the polarity and amount of current sent to the motor.

### **Servo**

A servo “motor” is actually a package that contains a small DC motor, a gearbox, and an encoder on the output shaft.

The interface for a servo is three wires. Two are for the power supply, the third is for the control signal.  This means you want to connect the power wires to their own dedicated power supply, but connect the signal to your microcontroller.

### **Stepper**

Stepper motors are common for control in printers, CNC machines, laser-cutters, and other applications where precise linear control is needed and the device can be plugged in.

Steppers are easy to design around (once they are calibrated) because you control it by sending the number of steps you want it to move. As long as it is not blocked by anything, it should move the exact number of steps you requested.

Like other motors, they need their own power supply. Unlike DC motors, stepper motors draw a ton of power – constantly. They draw power even when they are just holding their position. Compare this to a geared DC motor or servo motor that will naturally hold it’s position due to the friction of the gearbox – often requiring very little or no power unless it’s moving. This power draw means that stepper motors are not efficient and typically need a power supply that is plugged into a wall-outlet to deliver the power needed.

## **Serial Communication**

Serial communication is an established and common method of sending information between devices / environments. For example, connecting an Arduino board to a PC.

Each environment has it’s own requirements for establishing a serial connection. What’s common is that a serial port manager is required to establish the connection, maintain it, and close it (if applicable).

Neurons that need access to a serial port (like the SerialDriver and SerialSensor), can be dependent on a shared SerialNode. The SerialNode connects to the device (opens and manages the serial port). Then the Sensor and Driver use that Node.

### **SerialNode**

The SerialNode will need:

* an internal value (float) for every channel to store the most recent incoming value

* a way to name channels – could just use an index here… so channel numbers not names

* A method for checking the incoming-message-value. Used by SerialSensor.

* A method for sending messages (broadcasting a value). Used by SerialDriver.

### **SerialDriver**

The SerialDriver will need:

* To call a method on the SerialNode to send a message, but only when the Driver’s internal value changes

The Driver has a less complicated relationship with the Node than the Sensor does. The Driver can simply send messages by calling a method on the Node. The Node does not need to store these values.

Note that this breaks with the normal POL workflow (in which the Node would check the driver’s value). The SerialNode cannot have its InputNeuron set as there may be multiple Drivers that will be connected (each sending data on its own channel).

### **SerialSensor**

The SerialSensor will need:

* To call a method on the SerialNode to retrieve the value that it needs to set its own internal value

The SerialSensor needs to “subscribe” to the SerialNode – i.e. it needs to know when new messages come in. While this does not violate the normal Powder Of Life data flow, there are two issues. First, the Sensor parent class does not have a property because sensors do not have neuron inputs. Second, the SerialNode can offer multiple channels so we cannot use its single internal value.

This makes the relationship more complex (and does not fit the normal POL framework methodology). The Node will have an internal value for each incoming channel. Each SerialSensor will be assigned a particular channel and will use the Node’s corresponding internal value as its input.

### **Universal Applicability of Serial Neuron Trio**

For systems like this that require channel / port management, this trio of neurons model should work well. This could include: serial, 2-wire, UDP, OSC, etc.

### **Handling serial data**

While outgoing serial data is typically converted by the methods that write to the serial port, incoming serial data needs to be converted to the proper numeric type. Each language has specific constraints on how to handle this conversion.

#### ***Retrieving single characters from a string***

In Arduino (using C++), use the charAt() method on the String class.

	inputString.charAt(position)

In Unity (using C\#), use the string as an array.

	inputString[position]

### **AutoTalk**

I used the syntax from AutoTalk which wraps messages in both a start and end character.

	\<A:0.618\>

TODO, more… about this

# **Terms**

### **Abstraction**

TODO

### **Behavior**

The way the system acts overall is it’s **behavior**. This assessment can be applied to physical movement (as in a robot), visualizations (on screen, etc.), or to raw output (charted via scope, etc.). This assessment can be informal to allow for descriptive language that will be helpful in understanding the subtle nuances that matter in terms of how the system is perceived.

### **Component**

A **component** is a collection of parts that do something useful in the context of a specific problem / solution space. This distinction is somewhat arbitrary (defined by the designer / engineer) to allow for the inclusion / exclusion of parts to create the optimal arrangement at that specific scope. Well defined components allow you to connect them to other components in the system to design for desired behavior.

### **Compartmentalization**

In the engineering context, **compartmentalization** means the act of gathering functionality into the tightest possible scope. In software development, if you have a function that is doing two things, it should be broken into two functions. This will allow you to use either function separately if needed. If you want both functions together, you create a third function and wrap both of them within it.

### **Environment**

An **environment** is the conceptual “place” where development happens. This could be a primarily software domain such as a game engine like Unity (C\#, audio/visual output). It could be a mixed hardware / software environment like Arduino (C++, electrical engineering). Or it could be a primarily hardware domain like building modular robotics (rapid prototyping, mechanical engineering).

### **Framework**

The term **framework** describes the rules (methods and assumptions) that give POL its structure. By using this framework, you will need to conform to these rules (which is true of any framework). The rules of the framework define how development needs to proceed within a particular environment.

### **Idealized**

TODO

### **Interface**

In the context of components being connected together, an **interface** is the way two components communicate. If this interface is not standardized, the components cannot be connected easily and this hinders experimentation and development. The interface is simply an expectation that all components will use similar inputs and outputs so they can be connected easily (see interoperability).

### **Interoperability**

The **interoperability** of a component describes the degree to which it can be connected with other components. This interoperability is enabled by the standardization of the interface between those components.

### **Network**

A **network** is a collection of neurons that are connected together (“wired” together) to allow a constant flow of data from one neuron to the next.

### **Neurons**

#### ***Neuron***

In POL (in supported environments), a **neuron** is the base component type from which other components are derived. This means that all components are “neurons” through inheritance, though they will normally be referred to by their specific type. The neuron base type establishes how components share data.

There are several sub-types that inherit their structure from neuron:

* sensors

* drivers

* nodes

* (generators could just be nodes right?)

#### ***Sensor***

A **sensor** is a component that is designed to be connected directly to input and begin the flow of data through a network.

#### ***Driver***

A **driver** is a component that is designed to be connected directly to output and is at the end of a data-flow in the network. It is connected to a single input neuron that effectively sets its value.

#### ***Node***

A **node** is a component that can be either (or both) an input and/or output component. A node is a neuron designed to have whatever structure is needed for the purpose. For example, a MixNode has two input neurons that are merged into a single output, while the SerialNode is connected directly to the serial port and is then utilized by sensors and drivers that need to use that port.

### **Normalization**

When working with data, **normalization** refers to choosing a range (using minimum and maximum values) and then mapping all data to that range to allow all the data to fit within the scale implied by that range. Ideally, all values can be mapped to a 0-1 scale so that we can compare, contrast, and combine values as they move through the network. Having normalized values allows you to build analog logic and target specific behavior.

### **Read Forward**

Neurons in POL “**read forward**”. This means that data migrates through the network by neurons reading the state of the neuron that precedes it.

The most simple type of network has just two neurons. The data flow begins with a sensor (conveying an input such as an analog joystick). The sensor creates its own internal value based on its settings (normalization, etc.). Next we have a driver (relating an output such as controlling a motor). The driver has been set to use the sensor as its InputNeuron. When the driver reads the value of the sensor, the data flows “forward” through the network – from sensor to driver. When you move the joystick, the motor moves.

#### ***Branching / Bottlenecking***

A consequence of the read-forward architecture, is that each neuron can listen to a single source (**bottlenecking**), but broadcast to many audience members (**branching**). This means that signals can easily branch, but are trickier to bottleneck.

Partly, this is because bottlenecking requires decision making. When you merge two signals, you need to decide how to merge them. When you split a signal, i.e. branching, you can make as many copies as you like without deciding anything (they are all identical).

In POL you can merge signals, but there are specialized neurons for this (e.g. the MixNode). This is similar to how other flow processing paradigms work (like node-and-wire interfaces for audio / video work or in scenario building for e-learning).

Note that this is kind of backward from how a biological neural network works (like in our brain). The neurons in our own body have multiple inputs, dendrites, (sources) from which they infer how to react based on the weights of the inputs and the pattern. The biological neuron then broadcasts out the axon to only few or single (audience) neurons. Extending the point above, you can say that all that bottlenecking means the brain makes lots and lots of decisions.

# **References**

## **Doug Engelbart**

* Augmenting Human Intellect (1962)

* H-LAM/T (Human using Language, Artifacts, Methodology, in which he is Trained)

* “If there is any one thing upon which this 'intelligence depends' it would seem to be organization.” ([2c1e](https://www.dougengelbart.org/pubs/augment-3906.html#2c1e) )

* "man-machine interface", now called human-computer interface (HCI)

## **Vannevar Bush**

* As We May Think (1945)

* differential analyzer

TODO, add more…

## **POL is like…**

* The Powder of Life from the Wizard of Oz series in that you “sprinkle” some into your project and behavior “magically” emgerges.

* A cordycep fungus in that it threads itself through a system to gain high-level control (see The Last of Us)

* A human-centipede from the 2009 movie of the same name in that the data flows through the network in a single direction

* The Borg from Star Trek in that as it enters new environments (as development proceeds into new environments) POL learns new tricks that can be adopted system-wide.