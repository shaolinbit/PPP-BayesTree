/** @file   nonBiasStates.cpp
 * @brief  non-bias state vector -- {x,y,z,cb,tz}
 * @author Ryan Watson
 */

#include "nonBiasStates.h"
#include <cmath>
#include <iostream>
#include "miniblas/miniblas.h"

using namespace std;



/* ************************************************************************* */
double nonBiasStates::distance(const nonBiasStates &q,minimatrix* H1,     //
                               minimatrix* H2) const
{
    return GNSS_distance5(*this,q,H1,H2);
}

double nonBiasStates::norm(minimatrix* H) const
{
    return GNSS_norm5(*this, H);
}

double nonBiasStates::dot(const nonBiasStates &q, minimatrix* H1,     //
                          minimatrix* H2) const
{
    return GNSS_dot(*this, q, H1, H2);
}

/* ************************************************************************* */
ostream &operator<<(ostream &os, const nonBiasStates& p)
{
    os << "   " << '[' << p.x() << ", " << p.y() << ", " << p.z() << ", " << p.cb() << ", " << p.tz() << "]'";
    return os;
}


/* ************************************************************************* */
double GNSS_distance5(const nonBiasStates &p1, const nonBiasStates &q, minimatrix* H1,     //
                      minimatrix* H2)
{
    // double range = (q - p1).norm();
    minivector rr(q.size1);
    minivector_sub(&rr,q,p1);
    //double range =gsl_blas_sqrt_dnrm2(rr);
    double range=miniblas_dnrm2(&rr);

    if (H1!=NULL)
    {
        //H1->resize(1,5);
        //*H1 << p1.x() - q.x(), p1.y() - q.y(), p1.z() - q.z(), p1.cb() - q.cb(), p1.tz() - q.tz();
        //*H1 = *H1 *(1. / range);
        minimatrix_resize(H1,1,5);
        H1->data[0]=p1.x() - q.x();
        H1->data[1]=p1.y() - q.y();
        H1->data[2]=p1.z() - q.z();
        H1->data[3]=p1.cb() - q.cb();
        H1->data[4]= p1.tz() - q.tz();
        minimatrix_scale(H1,1./range);

    }
    if (H2!=NULL)
    {
        // H2->resize(1,5);
        //*H2 << -p1.x() + q.x(), -p1.y() + q.y(), -p1.z() + q.z(), -q.cb() + q.cb(), -p1.tz() + q.tz();
        // *H2 = *H2 *(1. / range);

        minimatrix_resize(H2,1,5);
        H2->data[0]=-p1.x() + q.x();
        H2->data[1]=-p1.y() + q.y();
        H2->data[2]=-p1.z() + q.z();
        H2->data[3]=-q.cb() + q.cb();
        H2->data[4]=-p1.tz() + q.tz();

        minimatrix_scale(H2,1./range);

    }
    return range;
}

// returns estimated pseudoragne
double GNSS_norm5(const nonBiasStates &p, minimatrix* H)
{
    double r = sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z()) + p.cb() + p.tz();
    if (H!=NULL)
    {
        minimatrix_resize(H,1,5);
        if (fabs(r) > 1e-10)
        {
            // *H << p.x() / r, p.y() / r, p.z() / r, 1, 1;
            H->data[0]=p.x()/r;
            H->data[1]=p.y()/r;
            H->data[2]=p.z()/r;
            H->data[3]=1;
            H->data[4]=1;
        }
        else
        {
            //*H << 1, 1, 1, 1, 1;  // really infinity, why 1 ?
            H->data[0]=1;
            H->data[1]=1;
            H->data[2]=1;
            H->data[3]=1;
            H->data[4]=1;
        }

    }
    return r;
}

double GNSS_dot(const nonBiasStates &p, const nonBiasStates &q, minimatrix* H1,     //
                minimatrix* H2)
{
    if (H1!=NULL)
    {
        minimatrix_resize(H1,1,5);
        //*H1 << q.x(), q.y(), q.z(), q.cb(), q.tz();
        H1->data[0]=q.x();
        H1->data[1]= q.y();
        H1->data[2]= q.z();
        H1->data[3]= q.cb();
        H1->data[4]=q.tz();


    }
    if (H2!=NULL)
    {
        minimatrix_resize(H2,1,5);
        // *H2 << p.x(), p.y(), p.z(), p.cb(), p.tz();
        H1->data[0]=p.x();
        H1->data[1]=p.y();
        H1->data[2]=p.z();
        H1->data[3]=p.cb();
        H1->data[4]=p.tz();
    }
    return p.x() * q.x() + p.y() * q.y() + p.z() * q.z() + p.cb() * q.cb() + p.tz()*q.tz();
}

/* ************************************************************************* */
ostream &operator<<(ostream &os, const nonBiasPair &p)
{
    //os << p.first << " <-> " << p.second;
    //os <<
    minivector_ostream(os,p.first);
    os << " <-> " <<endl;
    minivector_ostream(os,p.second);
    return os;
}
/* ************************************************************************* */

