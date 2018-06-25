using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HitCamera : MonoBehaviour {

    private YureCamera yureCamera;
	// Use this for initialization
	void Start ()
    {
        yureCamera = GetComponent<YureCamera>();
	}
	
	// Update is called once per frame
	void Update ()
    {
		
	}
    public void OnTriggerEnter(Collider xhit)
    {
        switch (xhit.gameObject.tag)
        {
            case "EnemyHit":
                //yureCamera.Shake(gameObject);
                break;
            case "WolfHit":
                //yureCamera.Shake(gameObject);
                break;
            case "HobgoHit":
                //yureCamera.Shake(gameObject);
                break;
            case "goblinHit":
                //yureCamera.Shake(gameObject);
                break;
            case "TrollHit":
                //yureCamera.Shake(gameObject);
                break;
        }
    }
}
