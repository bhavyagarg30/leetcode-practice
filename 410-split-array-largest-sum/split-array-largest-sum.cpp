class Solution {
public:
    bool isPossible(vector<int>& nums, int k, int mid) {
        int count = 1, sum = 0;

        for (int x : nums) {
            if (sum + x > mid) {
                count++;
                sum = x;
            } else {
                sum += x;
            }
        }

        return count <= k;
    }

    int splitArray(vector<int>& nums, int k) {
        int low = *max_element(nums.begin(), nums.end());
        int high = accumulate(nums.begin(), nums.end(), 0);

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(nums, k, mid))
                high = mid - 1;
            else
                low = mid + 1;
        }

        return low;
    }
};