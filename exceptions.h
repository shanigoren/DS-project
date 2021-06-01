#ifndef EXCEPTIONS
#define EXCEPTIONS

    class Exceptions : public std::exception
    {
        // protected:
        //     StatusType error;
        public:
            Exceptions() {}
            virtual ~Exceptions() {}
            // virtual const char* what() const noexcept
            // {
            //     return error;
            // }
    };

    class Failure : public Exceptions 
    {
        public:
            Failure() : Exceptions() {}
            virtual ~Failure() {}
    };

    class InvalidInput : public Exceptions 
    {
        public:
            InvalidInput() : Exceptions() {}
            virtual ~InvalidInput() {}
    };

#endif //EXCEPTIONS