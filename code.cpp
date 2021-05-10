typedef pair<int,int>p;
class Twitter {
public:
    /** Initialize your data structure here. */
    int x;
    unordered_map<int,unordered_set<int> >follow_unfollow_map;
            //follower          //followee
    unordered_map<int,priority_queue<p,vector<p>,greater<p> > >tweetByUserAndFollowers;
    //            userId         recentTweet  tweetId
    Twitter() {
        x = 0;
    }
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        tweetByUserAndFollowers[userId].push({x,tweetId});
        if(tweetByUserAndFollowers[userId].size()>10)tweetByUserAndFollowers[userId].pop();
        x++;
        
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int>ans;
        priority_queue<p,vector<p>,greater<p> >pq2;
        if(tweetByUserAndFollowers.count(userId)){
            priority_queue<p,vector<p>,greater<p> >pq = tweetByUserAndFollowers[userId];    
            while(!pq.empty()){
                pq2.push(pq.top());
                if(pq2.size()>10)pq2.pop();
                pq.pop();
            }
            
        }
        for(auto x:follow_unfollow_map[userId]){
             priority_queue<p,vector<p>,greater<p> >pq = tweetByUserAndFollowers[x];
             while(!pq.empty()){
                pq2.push(pq.top());
                if(pq2.size()>10)pq2.pop();
                pq.pop();
            }
        }
        
        while(!pq2.empty()){
            ans.push_back(pq2.top().second);
                pq2.pop();
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        follow_unfollow_map[followerId].insert(followeeId);  
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        follow_unfollow_map[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
