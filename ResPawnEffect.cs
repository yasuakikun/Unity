using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResPawnEffect : MonoBehaviour {
    [SerializeField]
    private GameObject effectobj;
    //消す時間
    [SerializeField]
    private float deltetime;
    //エフェクトのオフセット
    [SerializeField]
    private float offset;

	// Use this for initialization
	void Start ()
    {
        var Effect = GameObject.Instantiate(effectobj,transform.position + new Vector3(0f, offset, 0f), Quaternion.identity) as GameObject;
        Destroy(Effect, deltetime);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
