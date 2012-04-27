<?php
/**
 * @file hstatus.db.inc
 * Manages the database queries for the hstatus module.
 * 
 * I chose to put this in a separate file for two reasons.
 *  - It keeps the code cleaner in the other files.
 *  - It gives more flexibility if we should change the db structure.
 */
 
/**
 * hstatus_load_user
 * 
 * Arguments:
 *  1. $username - RIT DCE
 *  2. $loadCourses - NOT YET SUPPORTED
 *  3. $loadSubmissions - NOT YET SUPPORTED
 *  4. $reset - forces loading of a new user object instead of using the cache.
 * 
 * Loads an hstatus user object.  This function is very complex because it
 * uses a smart caching system to improve performance.
 * 
 * Structure
 *      -basic
 *          -name
 *              -firstname
 *              -lastname
 *          -active
 *          -college
 *          -department
 *          -program
 *          -gpa
 *      -continuation
 *          -status
 *          -cl
 *          -college
 *          -courses
 *          -gpa
 *      -points
 *          -points
 *          -waivers
 *          -courses
 *          -total
 *      -courses (optional, NOT YET SUPPORTED)
 *          array of (course, name, professor, quarter, grade, credits, honors)
 *      -submissions (optional, NOT YET SUPPORTED)
 *          -to be determined
 */
 
function hstatus_load_user($username, $loadCourses = false, $loadSubmissions = false, $reset = false){
    //allows short-term caching (within each page load)
    static $husers;
    
    /*check the short term cache in the static variable $husers.
    * The decision making process is as follows:
    *   1. check if caches should be used at all from the $reset variable.
    *   2. check to see if the user is available in the array
    *   3. if we don't have to load courses or submissions then it is guaranteed
    *       to be everything that we need in the object.
    */
    if(!$reset && isset($husers[$username]) 
            && !($loadCourses || $loadSubmissions)){
        return $husers[$username];
    }
    
    //Query Definitions 
    $q_basic = 
    "SELECT 
        student.firstname fname, 
        student.lastname lname, 
        student.college college, 
        student.department dpt, 
        student.program program, 
        student.active active, 
        gpas.gpa gpa
     FROM {h_students} student
     JOIN {h_students_gpa} gpas
        ON student.username = gpas.username
     WHERE student.username = '%s'
     LIMIT 1";
    $q_pts = "SELECT username, sum(numPoints) total
                FROM {h_students_points}
                WHERE username = '%s'
                GROUP BY username";
    $q_cpts = "SELECT username, sum(credits) total
                FROM {h_students_courses}
                WHERE username = '%s'
                GROUP BY username";
    $q_wpts = "SELECT username, sum(credits) total
                FROM h_students_waivers
                WHERE username = '%s'
                GROUP BY username";
    $q_continue = 
    "SELECT status, comp_learn, college, courses, gpa
     FROM {h_continuation}
     WHERE username = '%s'
     LIMIT 1";
    $q_courses = 
    "SELECT course, name, professor, quarter, grade, credits, honors
     FROM {h_students_courses} courses
     WHERE courses.username = '%s'
     LIMIT 1";
    $q_submissions = ""; //TODO: write this.
    
    // is it in the short term cache?
    if(!$reset && isset($husers[$username])){
        $u = $husers[$username];
    // is it in the long term (database) cache?
    } else if(!$reset 
            && ($cache = cache_get("hstatus_user:$username",'cache_honors')) 
            && !empty($cache->data)) {
        // all cached data in the db cache is serialized.
        $u = unserialize($cache->data);
    // fetch new data.
    // Note that this will fail if the user lacks an entry in either the h_students
    // or the h_continuation table.
    } else {
        // Fetch Basic Info
        $rs = db_query($q_basic, $username,$username,$username,$username);
        $arry = db_fetch_array($rs);
        if($arry){
            $u['basic'] = array(
                'name' => array(
                    'firstname' => $arry['fname'],
                    'lastname' => $arry['lname'],
                ),
                'active' => $arry['active'],
                'college' => $arry['college'],
                'department' => $arry['dpt'],
                'program' => $arry['program'],
                'gpa' => $arry['gpa'],
            );
        }else{ return false; }
        
        // Fetch Continuation Info
        $rs = db_query($q_continue, $username);
        $arry = db_fetch_array($rs);
        if($arry){
            $u['continuation'] = array(
                'status' => $arry['status'],
                'cl' => $arry['comp_learn'],
                'college' => $arry['college'],
                'courses' => $arry['courses'],
                'gpa' => $arry['gpa'],
            );
        }else{return false;}
        
        // Fetch Points
        // All of this might get changed later if we add columns to the h_students
        // table that store this information (those would be updated via cron)
        $u['points'] = array(
            'points' => 0,
            'courses' => 0,
            'waivers' => 0,
            'total' => 0,
        );
        //keep track of total points
        $total = 0;
        //points from point submissions like trips, research, etc
        $rs = db_query($q_pts, $username);
        $arry = db_fetch_array($rs);
        if($arry){
            $u['points']['points'] = $arry['total'];
            $total += $arry['total'];
        }
        //points from courses
        $rs = db_query($q_cpts, $username);
        $arry = db_fetch_array($rs);
        if($arry){
            $u['points']['courses'] = $arry['total'];
            $total += $arry['total'];
        }
        //points from waivers
        $rs = db_query($q_wpts, $username);
        $arry = db_fetch_array($rs);
        if($arry){
            $u['points']['waivers'] = $arry['total'];
            $total += $arry['total'];
        }
        //total points
        $u['points']['total'] = $total;
        
        //store data in cache with 2 hour lifetime.
        //this comes before the db queries for courses and submissions because we
        //don't cache the courses and submissions because they aren't always loaded.
        cache_set("hstatus_user:$username", serialize($u), 'cache_honors', time() + 2*60*60);
    }
    
                    // below needed in case of static variable load
    if($loadCourses && ($reset || !isset($u['courses']))){
        //TODO: implement
    }
    
    if($loadSubmissions && ($reset || !isset($u['submissions']))){
        //TODO: implement
    }
    
    $husers[$username] = $u;  //update static variable for future calls

    return (object) $u;
}
