#include "pose_manager.h"

void PoseManager::AddPose(NanoMapPose const& pose) {
	poses.push_back(pose);
}

void PoseManager::DeleteMemoryBeforeTime(NanoMapTime const& delete_time) {
	while (poses.size() >= 0) {
		NanoMapPose i = poses.at(0); 
		if ( (i.time.sec <= delete_time.sec) && (i.time.nsec < delete_time.nsec) ) {
			poses.pop_front();
		}
		else {
			break;
		}
	}
}

NanoMapTime PoseManager::GetMostRecentPoseTime() const {
	return poses.back().time;
}

bool PoseManager::CanInterpolatePoseAtTime(NanoMapTime const& query_time) const {
	NanoMapTime oldest_time = poses.front().time;
	NanoMapTime newest_time = poses.back().time;

	if ( (query_time.sec <= oldest_time.sec) && (query_time.nsec < oldest_time.nsec) ) {
		return false;
	}
	if ( (query_time.sec >= newest_time.sec) && (query_time.nsec > newest_time.nsec) ) {
		return false;
	}

	return true;
}

bool PoseManager::CanInterpolatePosesForTwoTimes(NanoMapTime const& time_from, NanoMapTime const& time_to) const {
	return (CanInterpolatePoseAtTime(time_from) && CanInterpolatePoseAtTime(time_to) );	
}