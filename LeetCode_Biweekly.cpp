class Solution {
struct SegMenTree
{
    vector<int> segtree;
    vector<bool> lazy;
    int n;
 
    void init(int _n)
    {
        n=1;
        while(n<_n)
            n=n*2;
        segtree.resize(2*n,0);
        lazy.resize(2*n,false);
    }
 
    void pUpdate(int node,int l,int r,int index,int val)
    {
        if(r-l==1)
        {
            segtree[node]=val;
            return;
        }
 
        int mid=(l+r)/2;
        if(index<mid)
            pUpdate(2*node+1,l,mid,index,val);
        else
            pUpdate(2*node+2,mid,r,index,val);
 
        segtree[node]=segtree[2*node+1]+segtree[2*node+2];
    }
 
    void propagate(int node,int l,int r)
    {
        if(!lazy[node])
            return;
 
        if(r-l==1)
        {
            segtree[node]=1-segtree[node];
        }
        else
        {
            segtree[node]=(r-l)-segtree[node];
            lazy[2*node+1]=!lazy[2*node+1];
            lazy[2*node+2]=!lazy[2*node+2];//this is a specific case like yaha par 2 operations means segment remains
            //same so we are doing this warna woh true wala hi rehta
        }
        lazy[node]=false;
    }
 
    void rupdate(int node,int l,int r,int i,int j)
    {
        propagate(node,l,r);
 
        if(r<=i || j<=l)
            return;
        if(i<=l && r<=j)
        {
            lazy[node]=1;
            propagate(node,l,r);
            return;
        }
 
        int mid=(l+r)/2;
        rupdate(2*node+1,l,mid,i,j);
        rupdate(2*node+2,mid,r,i,j);
 
        segtree[node]=segtree[2*node+1]+segtree[2*node+2];
    }
 
    int query(int node,int l,int r,int i,int j)
    {
        propagate(node,l,r);
 
        if(r<=i || j<=l)
            return 0;
        if(i<=l && r<=j)
            return segtree[node];
 
        int mid=(l+r)/2;
        return query(2*node+1,l,mid,i,j)+query(2*node+2,mid,r,i,j);
    }
};
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n=nums1.size();
        SegMenTree st;
        st.init(n);
        int sz=st.n;
        for(int i=0;i<n;i++)
            st.pUpdate(0,0,sz,i,nums1[i]);
        
        long long ans=0ll;
        for(auto ele : nums2)
            ans=ans+ele*1ll;
        
        vector<long long> output;
        for(auto query : queries)
        {
            int type=query[0];
            if(type==1)
            {
                int l=query[1];
                int r=query[2];
                st.rupdate(0,0,sz,l,r+1);
            }
            else if(type==2)
            {
                long long p=query[1];
                long long sum=st.query(0,0,sz,0,n+1);
                ans=ans+sum*p;
            }
            else
                output.push_back(ans);
        }
        return output;
    }
};
