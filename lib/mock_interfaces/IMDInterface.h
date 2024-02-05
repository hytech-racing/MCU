#ifndef IMDINTERFACE
#define IMDINTERFACE


class IMDInterface
{
    public:
        IMDInterface() {}
        bool high;
        bool ok_high() {return high;};
    private:
};


#endif /* IMDINTERFACE */
