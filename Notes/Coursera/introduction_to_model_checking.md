## Motivation of Verification 

Verification 
: The process of establishing the _truth_ or _validity_ of _something_
: The _rigorous_ process of establishing the _correctness_ of a computer system

Deadlock
: A state where all parties are stuck and cannot make further progress

### High-Profile Bugs 

- Pentium floating point division 
  - Missed entries in lookup table 
  - Cost ~$500 Million (1994 dollars)
- Ariane 5 Explosion
- Therac-25 Rad Machine 
- AT&T Telephone Network Outage
  - 9 hour outage in U.S. network 
  - Causes was a flaw embedded in the network switches

Challenges of bugs include external environments, nondeterminism, and system interactions.

### Cost of bugs

Most bugs are found early in the design lifecycle, and they are cheap to fix. However, 
toward the end of the design cycle bugs are less common but more expensive.

Typically there are 3 verification engineers for every 1 design engineer and verification 
takes 50%-70% of project resources.

## Principles of Model Checking | Chapter 1 | System Verification 

Information and Communication Technology (ICT)
: Digital computer system that process and exchange information (my definition)

When ICT systems fail it can be exceedingly expensive for both the customer and the 
producer. Small errors caused by a piece of software or defective hardware can damage entire 
systems and cause millions of dollars of damages. As the book says, "It is all about
money."

> The reliability of ICT systems is a key issue in the system design process.

System Verification 
: A technique "used to establish that the design or product under consideration possesses
certain properties."

### Verification Methods Beside Model Checking 

- Software
  - Peer review: a team of software engineers may statically analyze uncompiled code to check 
    it for correctness. Studies show that this captures around 60% of defects.
  - Software testing: predetermined inputs are given to a program, and it's tested to see if 
    the expected outputs are produced.
- Hardware 
  - Structural analysis: synthesis, timing analysis, equivalence checking 
  - Emulation: testing on an emulated circuit (maybe an FPGA or software equivalent?)
  - Simulation: yep

## Quiz 1 

I found the questions a bit confusing on Quiz 1. Question 1 was straightforward, but I think that 
questions 2 and 3 were a bit ambiguous. 

Question 2 had four possible answers, with only two of them making sense as potential correct 
answers but one of those also being something that could be argued against. In the list
below I give an outline of my thoughts on the answers to question 2, as well as suggestions 
for how the answers could be changed:

1. "Verification is easy"
   - This answer is clearly not correct, as demonstrated by the examples provided in module one.
     I think keeping this answer unchanged is great.
2. "Verification is nice but unnecessary for computer system design"
   - Again, I think this answer is clearly not correct. Module one give ample examples of why 
     verification is needed.
3. "Verification is critical to find difficult bugs"
   - I think this answer is ambiguous, as an argument could be made against it.
   - I would change the answer to: 
     
     "Due to complex interactions with the environment, difficult bugs may not be found without
     verification"

     (or something of the sort)

Question 3 was challenging for me to answer, because I found that all three of the possible 
answers could work, yet only two of them were correct.

1. "A computer system may have many components, checking all of them individually may take a 
   long time"
   - This is not one of the selected answers, I believe because Module 1 points out that typically 
     just checking each _component_ in a system is not the same as checking the entire _system_. 
     However, several of the verification strategies mentioned in Chapter 1 of "Principles of 
     Model Checking" do revolve around checking individual components, such as peer review of 
     software. Thus, with the knowledge the students have from Module 1 I think that this could 
     reasonably be interpreted as a _correct_ answer. 

     Also, as one who is a little more familiar with verification I would also say that the 
     "long time" required for verification is a challenge. For example, if you provide a C++ 
     library that has a large testing suite that tests all of your classes and functions, 
     the time associated with running that verification slows down the development process, 
     as when changes are made you need to wait for the tests to rerun.

2. "The target system may have huge state space"

   - This is definitely a challenge, but I don't believe the concept of a _state space_ is 
     introduced in Module 1, so students may be unsure as to what this answer is refering to.

3. "The target system may have both software and hardware components that involve complex 
   interactions."

   - I think this answer is clear and matches what was covered in Module 1.

# Overview of Verification 

NOTE: no introduction of state space

- Functional 
- Performance 
- Power 
- Security 
- Dependability

## Functional verification 

Functional Verification
: A process to ensure that the logic behavior of the system conforms to requirements.
: Aims to find _functional bugs_, or deviations from the logical specification
: Can be applied to finite or infinite state space systems 

## Techniques for Functional Verification 

NOTE: Confused whether these are for harware or software, just introduce that these are for hardware 
first.

- Simulation: Typically we have a _design model_ and a _golden model_. We give them an input stimulus, and 
  then check that the output of both models are equal.
  
  _Is very slow, and therefore can't cover all inputs._
  
- Post-silicon Testing: Runs at real hardware speed, but suffers from poor observability and controllability.
  
- Logic Emulation: Implement on FPGA, offers better speed that simulation, and better observability.
  
- Logic Equivalence: Aims to make sure that logic behavior of two designs are equivalent.
  
- Formal verification / model checking 
  - _Focus of this course_
  - Based on idea that design is represented by mathematical model and verified using mathematical 
    techniques.

NOTE: Reading specified for this section overlaps with reading from section 1.

### Challenges of Function Verification 

- System complexity growth 
- Slow simulation 
- Post-silicon testing is fast but difficult to debug

# Formal Verication and Model Checking 

Formal Verification 
: Proving or disproving the correctness of a model 
: Applied mathematical logic for modeling and analysis models 

Key elemants:
- System model 
- Formal specification 

Model Checking 
: A automatic technique that _yes_ or _no_ to the following: $ M \satisfies f $ where $M$ is 
the model, and $f$ is the correctness requirements.

# Elements of Model Checking 

State Transistion Models 
: A set of states connected by transistions 

> Any verification using model-based techniques is only as good as the model of the system 

A good thing about model checking is that making the model often provides another perspective 
on the model, and helps catch bugs even without verification. 

Safety
: Nothing bad happens 

Liveness 
: Good things eventually happen 

Fairness 
: Something happen infinitely often or repeatedly

