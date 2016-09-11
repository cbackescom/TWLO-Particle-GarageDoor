<?php

    // array of approved senders, indexed by phone number
    $people = array(
        "+15555551234"=>"DAD",
        "+15555559876"=>"MOM"
        "+15555555555"=>"CHILD"
    );

    // if sender is approved proceed to allow actions
    // if unknown, send them to NODICE!
    if($name = $people[$_REQUEST['From']]) {

        $key =   'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'; //put in your particle API key here
        $deviceID = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'; //put your particle device ID here

        if($_REQUEST['Body'] == "Status"){
                $door = 'Status';
                $statusURL = 'https://api.particle.io/v1/devices/'.$deviceID.'/status';
        }else if ($_REQUEST['Body'] == "D0"){
                $door = 'D0';
                $statusURL = 'https://api.particle.io/v1/devices/'.$deviceID.'/relay';
        }else if ($_REQUEST['Body'] == "D1"){
                $door = 'D1';
                $statusURL = 'https://api.particle.io/v1/devices/'.$deviceID.'/relay';
        }

        {
        $url = $statusURL;
        //pass your particle access token below
        $data = array('access_token' => $key, 'params' => $door);
        $options = array(
                'http' => array(
                'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
                'method'  => 'POST',
                'content' => http_build_query($data),
         )
        );

        $context  = stream_context_create($options);
        $result = file_get_contents($url, false, $context);
        var_dump($result);
        }
     }

    else {
    // NODICE! Sender was not in approved list so tell them to leave!
    header("content-type: text/xml");
    echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    echo "<Response>";
    echo "<Message>Why don't you make like a tree and get out of here!</Message>";
    echo "</Response>";
    }
?>
