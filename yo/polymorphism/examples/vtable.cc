    class Base
    {
        virtual void member();
    };
    inline void Base::member()
    {}
    class Derived: public Base
    {
        virtual void member();      // only declared
    };
    int main()
    {
        Derived d;  // Will compile, since all members were declared.
                    // Linking will fail, since we don't have the
                    // implementation of Derived::member()
    }
