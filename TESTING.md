testing strategy:
- using GTest for mocking systems 
- custom re-definitions of interfaces (for now)
    - cant use GTest mocking easily for this I dont think

- the mock interfaces will just be empty classes p much to have something that the systems classes can have pointers to if they own a pointer to an interface

- the mock systems will use the gmock lib for better mocking of systems for system to system interaction in the test env



