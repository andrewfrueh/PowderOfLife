# POL Manual

**Powder Of Life (POL)** is a framework and methodology for building interactive projects. It aims to simplify the process of connecting different components, such as sensors, motors, and software, to enable creative exploration and learning. POL provides a structured approach to problem-solving and building, offering both software libraries and hardware designs. 

**POL's Origins:**

* The name originates from L. Frank Baum's Oz series, symbolizing the ability to bring inanimate objects to life.
* POL was developed to address the challenges faced by students in new media art classes, particularly in integrating electrical, mechanical, and software elements.

**POL's Philosophy:**

* Inspired by thinkers like Valentino Braitenberg, Seymour Papert, Vannevar Bush, and Doug Englebart.
* Aims to create a system where simple components can be rearranged to produce complex behaviors.
* Focuses on providing idealized artifacts as building blocks and educational tools.
* Promotes physical computing as a means to enhance engineering skills and create dynamic interactions.

**Development Rules:**

* Components should be abstract, compartmentalized, reusable, and easily understood.
* Data should be normalized to a 0-1 range for interoperability.
* Data flow within components should be consistent and read-forward.

**Types of Systems:**

* POL supports a wide array of systems, including:
    * **Encoders:** Used for position sensing in mechanical systems.
    * **Motors:** Provide movement and act as the "muscles" of projects.
        * DC motors (standard and geared): Controlled by direction and speed signals.
        * Stepper motors: Offer precise linear control, commonly used in printers and CNC machines.
    * **Serial Communication:** Enables communication between devices, such as Arduino and a PC.

**API / Reference:** [API](API/)

**You can find examples of POL in use on the creator's website:** [https://andrewfrueh.com]. 

This page summarizes the core concepts and features of POL based on the provided manual excerpts. For detailed information and specific component functionalities, refer to the complete POL manual and API documentation (link to be provided).
